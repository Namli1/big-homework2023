# 大作业

所有代码也在Github上，请查看[Namli1/big-homework2023](https://github.com/Namli1/big-homework2023)

# 设计说明书

## 分工
因为我们程序有很多模块，分工是比较容易的，我们各自就完成了独立的模块，然后可以互相用实现的函数。为了明确地说明一个函数或者模块是由谁实现的，我们在代码和下面设计说明添加了注释，指出模块/函数由谁写的。

## 文件结构
为了提高我们程序代码的清晰度，我们把文件分成多个目录，每个文件夹里面有功能相关的函数和类型。希望助教也没有问题了解我们的结构，可以看下面的说明了解各个模块，但可能也需要看一下代码，了解函数和类型之间的连接。

<br />
关于编码的困难部分而言，我们认为以下每个部分都存在某种形式的困难，在本报告中我们将详细解释我们克服这些困难以后的结果。我们在总结报告中对一些特别具有挑战性的编码部分进行了反思，请查看总结包好了解我们难点以及解决方法。
<br />

## 类设计（Models）-*一起*
类图：
![](images/class-diagram.png)

关于我们的类结构，我们首先应该从`Building`类开始。这个类是`Canteen`类的父类，参数为名称和位置，以及相应的获取函数。我们选择创建这个类是因为在定位器模块中（见下文），用户可以从校园内的建筑列表中选择来确定他的位置，这也包括非食堂的建筑，所以只用`Canteen`不太好。

`Building`类的位置参数的类型是`LatLng`，其类只有`latitude`和`longitude`参数。因为这个类跟定位器密切相关，我们在下面定位器的章节来了解这个类。

`Canteen`类是`Building`类的继承类，所以也有名称和位置参数。但食堂还有很多其他数据。
每个食堂也最多有三个开放时间，存储在数组`opening_times`中，还有两个向量描述食堂的饭菜，即`signature_meals`向量和`meals`向量。这种分离是为了保存食堂最有名的饭菜，但当使用函数`getMeals()`时，这两个向量将被合并，并返回所有饭菜。
下面是对类的每个函数的一个简单的描述：
- `favourite()`:这个函数是用于收藏这个食堂，使用下面说明的文件读写存储食堂的名称。
- `display_information()`:该函数会输出食堂的信息，包括名称、开放时间、著名菜、位置和最近的建筑。
- `getSignatureMeals()`: 函数会返回`signature_meals`向量。
- `getSignatureMealsList`: 函数将返回由逗号分隔的`signature_meals`向量数据。
- `getMeals()`: 函数会返回所有菜，把`meals`和`signature_meals`合并，注意返回值是set，因为每个饭菜只能一次出现。
- `getIngredients`: 将返回饭菜包含的所有配料，可以用`includeOptional`参数选择是否包括不必要的配料。返回值也是一个set，为了确保不会重复常用的配料。
- `containsIngredients`: 该函数检查一个食堂是否包含一组给定的配料数组（只包含一个是会返回true，并相应地返回一个布尔值。它使用帮助模块中的`setContains`函数，请下面查看。
- 最后需要实现运算符重载，因为我们在过滤器模块使用一个`Canteen`类的set数组，而且set需要这个量运算符为了核对一个食堂对象是否已经存在在set内。

`Meal`类在我们程序很重要，它存储饭菜的信息。该类有饭菜名称和饭菜配料数组，并相应的获取函数。然后也需要重在运算符，和`Canteen`类同样的道理，因为`Meal`类在set数组中使用，set数组就要求我们实现运算符重载。

`Optionality`其实只是一个结构体，但是用法很有意思。我们的想法是，某个饭菜中可能有不用加的配料，例如点炒饭的时候也可以不加肉。这个可选性由`Optionality`类实现，只是`Ingredient`枚举的一种包装，因为枚举本身只能有一种信息。

最后由`Ingredient`枚举，它能以一种标准化的方式表示所有的配料，使得过滤更加方便。因为食品成分变化不大，而且食堂使用的配料有限（尽管配料很多，但不熟无限的），我们认为用枚举表示配料是很合理的。



## 国际化模块 (i18n) *-栗思祺*

我们的国际化模块包括三个主要功能：文本翻译、日期格式转化和货币兑换。为了统一这三个功能而且提供方便的使用方法，我们设计了一个i18n类：
```c++
class I18N {
   private:
       static char locale[3];
       static char default_locale[3];
       string insertVariables(string text, const vector<string>& replacements);
       string formatDate(unsigned short year, unsigned short month, unsigned short day, string format);
   public:
       const string gettext(string text, int amount=1, const vector<string>& vars=DEFAULT_VECTOR);
       string getCurrency(int amount, string currency_code);
       string getFormattedDate(unsigned short year, unsigned short month, unsigned short day, string format="default");
       static void changeLocale(char newLocale[3]);
};
```
首先，这个类需要存储系统目前选择的语言以及系统的默认语言（`locale` 和 `default_locale`）。他们是static因为所有i18n对象应该都有一样的语言，否则的话会带来问题，程序的一部分可能是中文的而另外一个部分是英文的，这样用户体验很差。

private中的两个函数是类内使用的，所以不用透露它们。public中的gettext函数是翻译文本的主要函数，我们下面仔细看一下它是如何实现翻译功能。

gettext函数简单来说会查询一个数组变数且找到数组中符合string参数的映射条目，然后输出相应的翻译词。我们使用的数组是由Translation结构体构成的。Translation的基本结构体如下：
```c++
struct Translation {
    string msgid; //Message ID (in English)
    map<string, string> translations; //Translations map
    string msg_plural; //Message in plural
    map<string, string> plural_translations; //Translation for plural
};
```
Translation类的msgid是要翻译的句子，整个程序中msgid需要有统一的语言，在我们程序中是英文。这个句子的翻译词是在translation属性存储的。我们来举一个例子更好的解释他的功能。

假设程序员要翻译这个句子：`cout << "Hello World" << endl; `。使用我们i18n模块，程序员可以调用i18n.gettext()的函数，如：
```c++ 
cout << i18n.gettext("Hello World") << endl;
```
最后需要创造符合`"Hello World"`的数组条目。如：
```c++
static const unsigned int translation_count = 1;
static const Translation allTranslations[translation_count] = {
    {
        "Hello, world!", {
            {"de", "Hallo, Welt!"},
            {"fr", "Bonjour le monde!"},
            {"es", "¡Hola mundo!"},
            {"zh", "世界好！"},
        }
    },
}
```
运行程序时，gettext函数会找到allTranslations数组中的`"Hello, world!"项目，而且找到符合目前选择语言的翻译词，最后返回此值。

但gettext还有另外两个功能。Translation类也可以存储复数形式的翻译词，比如英文中会说"1 **person**"，但是如果有多个人，我们会说"2 **people**"。所以英文（其他语言也有这样的特点）词会根据数量而变。我们的Translation类允许定义两种参数，一个是单数形式的词，然后也可以定义复数形式的词（但也不需要）。
例如：
```c++
    //单数：
    "person", { 
        {"de", "Person"},
        {"zh", "人"},
    },
    //复数：
    "people", { 
        {"de", "Personen"},
        {"zh", "个人"},
    }
```
程序员可以给gettext函数一个amount参数，如果给的话，函数会自动的选择单数或者复数的形式，返回相应的string。

另外的一个功能是如果字符串中需要包含变数，这个对翻译功能来说会带来困难，因为变数也不能翻译，而且如果分开字符串为变数前和变数后的两个字符串，那翻译者可能读不出来原来句子是什么意思。所以我们gettext函数提供一个传递变数的功能，可以在原来的字符串用"%S"来代替变数的位置，然后gettext会先翻译句子，然后插入变数的值。使用法如下：
```c++
vector<string> replacements = {"Ben", "Paris"};
string translated = i18n.gettext("%s is currently in %s", 1, replacements);
cout << "Translated text: " << translated << endl; 
//会输出："Translated text: Ben is currently in Paris"
```
函数会按照vector的顺序代替相应的%s值。

如果想自己尝试一下gettext函数的功能，可以复制i18n.cpp文件中的testI18N()函数在main.cpp调用。

***

i18n还有`getCurrency`和`getFormattedDate`的函数。

`getCurrency`函数可以将一笔人民币金额兑换成另一种货币。为此，i18n文件有`currency_conversions`数组，它保存了世界上不同货币的货币以简名及它们与人民币的兑换率。函数将所需的货币简名和金额作为输入参数，然后将金额转换并四舍五入到小数点后两位，然后返回一个字符串。

`getFormattedDate`相对来说更复杂，它的功能是将一个日期转换成制定的日期格式。例如美国通常使用MM/DD/YYYY，而中国使用YYYY年MM月DD日的格式。
函数接受无符号整数的年、月和日参数，而且以y（=year/年），m（=month/月）和d=（day/日）构成的日期格式，比如"yy/dd/mm"或者"yyyy-mm-dd"。函数开始时会首先把格式字符串反转，目标是确保如果格式只包含yy，我们不要输出年前两个数位，而且后面的两个，因为函数会从年最后的数位开始替代y字。例如：
<br />
<br />
`yy-mm-dd` 反转-> `dd-mm-yy` -> 输入2023年10月21日 替代-> `12-01-32` 再次反转-> `23-10-21` (想要的日期格式)
<br />
<br />
每个国家有自己标准的日期格式，所以我们也定义了一些默认的日期格式，如果函数日期格式参数为`"default"`, 函数会参考`default_date_formats`数组使用现在选定语言的通用日期格式。

最后，i18n类还提供`changeLocale`函数，适用于改变目前的语言选择。通过文件读写，我们也把用户选择的语言存储下来，所以用户下次运行我们程序时，语言不会调到默认的语言。这个功能在i18n对象的构造函数实现，每次构造i18n对象，它会读取文件存储的语言，或者如果没有存储会使用默认语言。

## 定位器（Proximity）*-灏谛伦*
我们项目的距离搜索功能是最主要的功能之一；它能让用户根据给定的选择系列输入本人目前的位置，继而算出最近的食堂。另外，该功能也涉及到计算两个食堂/位置之间的距离，无需知道用户现在在什么位置。
<br />
<br />
那么，这是怎么实现的呢？首先，我们来看距离计算功能；距离计算功能基本上是按照半正矢公式（Haversine formula）而算出来的。这个公式说明任何两个点在一个半球的表面上之间的距离是多少，因为地球表面不是完美的半球，这仅是个理想模型但是用比较小的距离的话，它的准确度确实很高。Haversine公式为a = sin²(φB - φA/2) + cos φA * cos φB * sin²(λB - λA/2)， c = 2 * atan2( √a, √(1−a) )， d = R ⋅ c。式中d为最终的距离，φ指的是纬度，λ指的是经度。用c++实现这个计算的过程其实不太难。首先地图软件公布的纬度经度信息需要从度转到弧度才能代入公式里，然后通过#include \<cmath>，我们就能用pow，sqrt和atan2的关键词来进行计算。该公式也使用地球的半径，所以我们决定把这个值当作const变量值，在文件头定义了。
<br />
<br />
从Haversine公式，计算两个食堂之间的距离就能直接用它，但是为了计算离某座食堂最近的食堂（nearest canteen function）更复杂一些。在我们的食堂cpp文件我们定义了一个食堂数组，储存提前定义的一系列的食堂对象，包括他们的位置，名字等等。那么，在nearest canteen function里面我们首先使用一个for循环一个个用以上的Haversine公式来计算数组的i-th成员跟目前位置之间的距离，如果该距离比已经定义的最近距离变量小的话，函数用该距离赋值给nearest变量，到最后函数就返回nearest值。
<br />
<br />
判断目前位置功能`getCurrentLocation`让用户按照输出的指导输入一个数值选择目前的位置。还有，我们设计了verify功能来判断用户的输入是不是合适，如果不合适的话，让他们再次输入数值。这个verify功能是bool类的函数，判断输入的数值是否在给定的数值范围内。用户输入跟食堂相应的数值之后，函数找出canteen 数组里的相应对象，暂时保存为目前位置对象。
<br />
<br />
跟proximity功能相关的struct/class基本上有一个，虽然以上的函数都是用食堂类对象的，但是使用的成员变量都来自于`LatLng` struct。所以我要接着说明`LatLng`设计和数据。首先他有两个成员变量，纬度和经度，两个float类对象。他们是float而不是double的原因跟储存和执行速度有关，用float也能很准确地计算食堂之间的距离，不需要double提供的精确性。`LatLng`有一个默认构造函数，也有带参数的构造函数，让我们定义有位置信息的几个食堂`LatLng`对象。`LatLng`也带有\<\<的运算重载函数，让系统输出Lat/Long信息给用户看。
<br />
<br />
最后，bool类的`isWithinRange`函数对我们的过滤功能是不可缺少的，它的功能是判断某个食堂是否跟目前位置在给定的距离范围内，如果不是的话它会返回False值，让过滤器不输出那个食堂。
<br />
<br />
为了用户的方便，我们也设计了以上函数类似的三种函数，第一个返回最近食堂的距离，第二个返回它的名字，第三个返回该食堂的对象。这样我们可以给用户输出食堂的名字，距离和接着用最近食堂对象来继续进行别的功能，比如读写文件。

## 输入出（I/O） *-灏谛伦*
### 文件读写（File.h）
由于我们原来想让用户搜索食堂之后保存他们最喜欢的食堂，读写文件在我们项目中是很重要的。
<br />
首先我们设计了`writeFile` （写文件）函数。写文件的过程如下介绍；
1. 定义ofstream类的对象 
2. 用该对象开新的/已经创造的txt类文件 
3. 如果文件里没有想插入的食堂名字，用ios：：app态写食堂名字在里面 （app的意思是写在文件的最后部分，相当于增加信息，不是更新信息），
4. 用ofstream对象关文件。

然后file.cpp还有read和display功能。其一，readFile函数用ifstream对象开以上创造的文件，然后通过getline关键词，它一个个读文件的食堂信息，然后关文件。`displayFile`函数同理用ifstream对象开文件，用getline关键词一个个读文件的信息，继而一个个输出里面的食堂名字，最后关文件。
<br />
<br />
读写文件也有bool类的verify功能，判断文件里面是否已经包括想写入的食堂信息，它跟`readFile`函数同理用ifstream对象开关文件，读文件。我们觉得该功能很重要因为用户绝对不想系统display保存的食堂的时候多次输出同一个食堂。这样我们能避免这样的现象，避免系统给文件写入复制信息。
<br />
<br />
最后file.cpp 包括clearFile函数。它使用remove关键词删除食堂信息的txt文件，相当于 “clear” 保存的食堂。

### 操作台 (Console)
Console文件的主要功能是给我们提供很带有方便性的函数，让编程的过程越来越简单。首先包括`centrifyOutput`函数，用这个函数输出信息的时候，信息会出现在屏幕的中间位置。虽然这个是很次要的，我们还认为它能让整个系统变得更好看。然后我们设计了`printspace`函数，功能是把输出多个空格的过程很简单。`clearConsole`在用户方便方面是非常重要的，执行`clearConsole`函数的时候，它会把屏幕表示的信息去掉，基本上为了让新信息出现在屏幕上，这样让整个输出过程变得更梳理，避免用户看不懂屏幕乱乱的输出。`clearConsole`的代码依赖windows操作系统已经定义的关键词system加上一个字符串 “cls” ，告诉它把屏幕的信息去掉。
<br />
<br />
除此之外，console也定义const整型变量num_cols，主要为了实现`centrifyOutput`函数，它代表屏幕的宽度，给系统指导怎么计算centrify的输出放在哪个位置。最后，console文件有`changeColor`函数，让编程者或用户通过输入改变屏幕背景颜色或文字颜色。
<br />
<br />
Menus文件是我们项目中输出部分的代码中心。它包括各种各样的display函数，把系统的某个输出过程实现以及给用户表示在屏幕上。比如 `displayMainMenu`、`displayLocationSelectionMenu`、`displayNearestMenu`、`displayLocationMenu`等等。他们都基本上用输入cin和输出cout来带用户完成某种功能的过程，最后给用户输出功能的结果，比如最近食堂离目前位置的距离或列下用户已经保存的食堂。这些函数涉及到for和while循环、上述的verify函数、各种各样的函数叫呼、cout、cin、switch语句等等。

### Main
Main文件的功能很简单，它首先把屏幕的背景和文字颜色初始化，让背景为紫色，文字为黄色。然后它输出一个欢迎信息，最后执行mainMenu功能，让系统给用户输出应用的首页。



## 过滤器模块（Filter）*-栗思祺*

我们程序的过滤器可以通过四个参数过滤食堂。参数为最远距离、开放时间、要排除的配料和想吃的配料。
实现每个过滤参数分为两部分：首先需要把用户输入的文字解析到相应的类型（字符串不太好用），然后需要进行过滤。

### 解析文本
1. 最远距离
为此，我们需要确保用户输入了一个无符号的整数，因为距离在我们程序中以米为单位。很方便的是，我们在helpers.h文件里已经定义了一个`requestInteger`函数，就会确保用户输入的是无符号整数。

2. 开放时间
开放时间需要解析`OpenTime`的对象，为了用户方便输入可以输入12:00、12:00-14:00或者<21:00这类的文字机构。确保用户输入的格式没有错，我使用了正则表达式。通过三个正则表达式，我可以检查用户是否输入了与格式不符的内容而且请用户重新输入。如果想了解正则表达式，可以查看下面的解释。通过核实以后，函数会把用户输入的数据转换为OpenTime对象，然后把其返回。

3. 配料解析
排斥和包括配料的解析方法一样，所以使用的函数也一样。用户输入的格式为"x, y, z"(x、y等为配料)。函数首先去掉所有的空白，然后将逗号分隔的字符串解析成一个字符串的向量，然后使用`parseIngredient`函数来获得相应的枚举值。`parseIngredient`使用了一个名为magic_enum的外部库，它可以将字符串解析为枚举，外裤的更多信息在[此链接](https://github.com/Neargye/magic_enum)。最后，函数会返回Ingredient类的向量。

### 过滤器
该过滤器循环检查`data/canteens.cpp`中定义的每个食堂，然后检查每个食堂的过滤器要求。首先，太远的食堂被过滤掉了。然后，不包含用户指定的开放时间的食堂也被过滤掉了。最后，过滤器将用户指定的配料与食堂的配料进行比较，过滤掉那些有用户不喜欢的配料的食堂，而包括那些有用户想吃的配料的食堂。最后，函数会返回符合要求的向量。

### 正则表达式解释
`"^(>|<)(([0-1]?[0-9]|2[0-3]):[0-5][0-9])$"`
* `^`: 匹配字符串的开头。
* `(>|<)`: 匹配一个大于号或小于号字符，表示比较符号。
* `(([0-1]?[0-9]|2[0-3]):[0-5][0-9])`: 匹配一个时间，格式为 HH:MM，HH的范围为00到23之间的两位小时数，MM的范围为00到59之间的两位分钟数。
* `$`: 匹配字符串的结尾。


## 全局变量模块（Global）*-栗思祺*
我们唯一全局的变量是程序贯通使用的i18n对象，它在整个程序中应该统一，不用声明多个对象。因此，我们在global.cpp声明一个I18N类对象，叫i18n，然后使用i18n模块功能的文件可以包括global.h文件访问i18n对象。


## 食堂数据（Data）*-栗思祺*
我们关于食堂的数组是在程序的一个cpp文件存储的，而是不是在文件里。我们有意识地做出了这个决定，因为我们认为食堂数据不会有很大的变化而且用户也不要自己编写食堂信息，这很危险。如果食堂信息真的发生了变化应该更新程序，发布一个新的版本。所有数据使用我们上面描述的类和他们的构造函数，这个文件主要有数据，编程上的意义不大。可以注意的是，我们有一个canteen数组，列表所有食堂，而也有一个buildings数组，列表所有建筑。这是因为我们在定位模块中给用户提供校园内的几个建筑，也包括六教，所以需要分开存储canteens和buildings。为了避免不必要的重复定义，我将食堂和其他建筑合并在buildings阵列中，使用`mergeArrays`模板函数。

## 辅助函数（Helpers）*-一起*
辅助函数的目的是减少代码序列的重复，并提供方便的访问常用函数。下面是对每个函数的简短描述:

1. `bool isInteger(string str, bool withFeedback)`：这个函数接收一个字符串，并检查它是否是一个无符号整数。如果withFeedback为true，如果用户没有输入一个整数，就会提供反馈。
2. `int requestInteger(string& input)`: 这个函数基本上跟`isInteger`一样，不过它还会要求用户输入无符号整数，如果它没有的话
3. `bool verify(int choice, int lowestOption, int highestOption)`：这个函数只是检查一个给定的整数输入是否在一个给定的范围内。
4. `bool verifyChar(char input, char a, char b, bool ignoreCaps)`：这个函数检查一个给定的字符是否等于另外两个给定的字符，并且可以选择忽略大写字母。
5. `bool isThisCorrect(string message)`：这个函数要求用户反馈他所输入的内容是否正确，用户可以用Y/N回答。
6. `extern BaseT* mergeArrays(const T1* arr1, size_t size1, const T2* arr2, size_t size2)`: 该函数是为了合并两个数组，使用模板形式因为我们不知道要合并的数组有什么数据类型。由于c++内的限制，我不能把这个函数声明在.cpp文件中，只能在.h文件声明。这个函数在data模块被用，是为了合并`canteen`数组和`non_canteen_buildings`数组。
7. `extern bool setContains(set<T> set1, set<T> set2)`: 该函数是为了检查两个set数组是否包含同样的条目。也是通过模板形式实现，因为数据类型不明确，使用模板使这个函数的使用范围更大。函数在过滤器模块被用，是检查某个食堂是否有用户想/不想要的配料。
8. 剩下的函数容易理解，请查看源码中的注释

***
***
***
# 用户手册
哈喽！↖(^▽^)↗
欢迎使用我们的清华大学食堂探索系统！接着我要带你学会怎么使用我们的系统。

由于我们的程序使用外裤，我们对软件有最低要求，请确保编译和c++语言至少有以下版本:
- C++17
- Clang/LLVM >= 5
- MSVC++ >= 14.11 / Visual Studio >= 2017
- Xcode >= 10
- GCC >= 9
- MinGW >= 9

然后我们推荐使用VSCode，可以查看.vscode中的文件，它们为能够编译我们程序必不可少。然后可以使用Ctrl+Shift+B (mac是⇧⌘B)运行程序。如果有意外的话，请查看[此链接](https://code.visualstudio.com/docs/languages/cpp)。

使用指导：
### 打开软件，进入首页
- 打开软件后，你会看到我们的食堂探索系统首页，如下所示：
![](images/usage-1.png)
现在你可以看到首页给你七个选择——以下我要介绍每一个选择让你做什么，交给你如何用它。

1. List Canteens （搜索食堂）
- 在首页中输入 “1” ，系统会自动进入list canteens部分
![](images/usage-2.png)
- 如上所示，search canteens页给你机会看系统上所有的食堂
- 然后，按照系列的数值，请输入你想查询的食堂 “1-4”
- 用 “1” 为例，这样会让系统自动进入Qingfen （清芬园）的信息表示部分
![](images/usage-3.png)
- 如果输入 “1” 的话，系统会给你表示清芬园的食堂信息，包括开关时间、特殊菜，地图位置以及离它最近的食堂是哪个。读完信息之后，请输入0来回到首页。

2. 过滤器
- 在首页中输入 “2” ，系统会自动进入list canteens部分
过滤器提供四个选项：
    1. `Please enter the maximal distance to the canteen (in meters, no decimal places)`: 可以输入一个距离，一米为单位
    2. `Please enter the desired opening time (ex: >21:00, 17:00-15:00, 14:00)`: 可以输入一个时间，格式为HH:MM或HH:MM-HH:MM或\<HH:MM或>HH:MM。最后两个格式的意思是给时间前或之后。
    3. `Please enter *excluded* ingredients (like this: pork, cabbage, ...)`: 输入你想排除的所有配料
    4. `Please enter *included* ingredients (like this: beef, coriander, ...)`：输入你想要的所有配料
    > ！！注意！！：配料必须符合models/classes.cpp中的Ingredient枚举。只能输入Ingredient枚举值，但不用输入大写字母
    5. `Please select your current location`:输入你目前的位置，从建筑选择一个。
    最后程序会输出符合要求的食堂（如果有的话）。

3. What is the closest canteen? 距离功能
<br />
在首页中输入“3”的话，系统会自动进入食堂距离部分。
![](images/usage-4.png)
- 该部分有两个选择，前者是找到离你最近的食堂是哪个，后者是计算任何一个食堂跟你目前位置之间的距离。
- 我们先来看前者；输入 “1” ，系统会带你进入最近食堂部分
![](images/usage-5.png)
- 在最近食堂部分中，你首先需要确认你目前在哪里，请按照系统的输出输入相应的数值，确认你现在在哪里。
- 我们用 “1” 为例，输入 “1” 的话，系统会给你表示你选择的目前位置是Qingfen，然后问你这是不是正确。
![](images/usage-6.png)
- 如果正确的话，请输入Y
- 不正确的话，请输入N，再次选择你的目前位置在哪里。
- 最终确认目前位置之后，系统会给你输出离你最近的食堂是哪个，而它离你多远，如下图所示；
![](images/usage-7.png)
- 如果你想保存这个食堂作为最喜欢的食堂之一，请输入 “Y” ，不想的话输入 “N”
- 输入保存选择之后，系统会给你确认操作成功，然后请输入 “0” 来回到首页。
<br />
<br />

- 如果你选择查询任何一个食堂离你多远，请最初输入 “2” ，如系统所说，系统会带你进入距离计算部分
![](images/usage-8.png)
- 你首先需要确认你目前在哪里，请按照系统的输出输入相应的数值，确认你现在在哪里。
- 我们用 “1” 为例，输入 “1” 的话，系统会给你表示你选择的目前位置是Qingfen，然后问你这是不是正确。
![](images/usage-9.png)
- 如果正确的话，请输入Y
- 不正确的话，请输入N，再次选择你的目前位置在哪里。
- 确认目前位置之后，系统会给你问你的目的食堂是哪个，请按照系统的输出输入跟目的食堂相应的数值
![](images/usage-10.png)
- 我们用 “2” 为例，代表观畴园是我们的目的食堂，系统会给我们表示我们选择的目的食堂是观畴园，然后问我们这是不是正确
![](images/usage-11.png)
- 跟以上的确认过程一样，请输入Y还是N，如果需要的话再次选择目的食堂是哪个
- 确认目的食堂之后，系统会自动给我们表示目前位置和目的食堂之间的距离是多少，查询距离之后，请输入 “0” 来回到首页。
![](images/usage-12.png)

4. My Canteens （查询保存的食堂）
- 在首页中输入 “4” 的话，系统会自动进入查询保存的食堂部分。
![](images/usage-13.png)
- 如上图所示，因为我们之前在查询离我们最近的食堂是哪个，因为用清芬园为例，系统给我们机会保存最近食堂 （桃李园）到favourite canteens中。
- 这个部分基本上会列出你所有保存的食堂，如果没有的话，什么都不会输出。
- 查询之后，请输入 “0” 来回到首页。

5. Language/语言
- 在首页中输入 “5” 的话，系统会自动带你进入语言选择部分
![](images/usage-14.png)
- 软件的default语言是英文，如果你想改变系统使用的语言，请按照以下的指导去改变它。
- 请按照系统的输出选择你想系统用哪个语言输出信息，我们用 “2” 为例，代表选择中文为系统输出语言
![](images/usage-15.png)
- 选择语言之后，系统会自动回到首页，然后所有的输出从此之后会用那个语言输出信息。

6. Clear Cache （清洁缓存）
- 在首页中输入 “7” 的话，系统会自动带你进入清洁缓存部分
![](images/usage-16.png)
- 该部分只有给你确认操作成功，清洁了所有已经保存的食堂
- 请输入 “0” 来回到首页。

<br />
<br />
用户手册到此结束，我们希望你喜欢使用我们的系统！ 慢走！ ヽ(•‿•)ノ

***
***
***
# 总结报告

## 灏谛伦
我完成这个项目的经历总体上是一次积极的经历。首先，尽管我们在这学期的编码设计中涵盖了很多主题，但通过这个项目，我获得了很多关于C++的新知识。我个人认为，尽管课本上有很多细节，老师也讲得很详细，但学习如何使用代码的最好方法是将其付诸实践。通过这种方式，我发现了C++中某些概念的一些特殊用途和交互作用，而这些概念是教科书无法涵盖的。此外，由于该项目的规模，我们编写了数千行代码，所有代码都必须协同工作，这远远超出了教科书的范围，并带来了各种新的挑战，包括以各种组合将头文件和源文件合并在一起以实现代码。
<br />
从项目的困难方面而言，首先，我认为这个项目的规模使它变得困难；正如我上面提到的，因为我们有数千行代码和几个头文件，确保它们被组织起来并可以一起使用是我们必须克服的挑战，当然在这一过程中会遇到一些我们必须解决的问题。此外，作为一个两人的团队工作也带来了一些新的使用挑战，因为我们不可能总是在同一个房间里一起编码，我们很快意识到我们需要一种有效共享代码并将其组合在一起的方法。我们通过使用一个名为GitHub的网站来做到这一点，GitHub是一个代码共享网站，这使我们能够实时同步我们的代码，并有效地将我们的部分合并在一起。在我负责编写的代码方面，我面临的一些具体挑战如下：；首先，设计控制台和输出功能在调用函数和创建对象的方式以及处理类的私有成员变量方面提出了各种挑战。我必须确保函数能够被正确调用，使用正确的对象和正确的数据来输出正确的结果。其次，由于我们没有在课堂上讨论这个主题，实现文件读写是一个挑战，我不得不花很多时间检查在线资源和课本，以将这些概念应用到我们的代码中，这当然是一个问题，但最终我为我们在这方面取得的成就感到骄傲。最后，实现所有的PROXIMITY函数带来了很多挑战，尤其是因为它们的许多函数都使用了私有成员变量，此外，逻辑必须清晰简洁，我必须考虑如何编写高效的代码，让阅读它的人都能清楚地理解。
<br />
最后，作为一个团队，我们遇到了一些挑战，包括使我们分别编写的代码的不同部分协同工作的复杂性。我们经常不得不花时间在同一个房间里，互相解释我们的进展，并共同努力将我们的代码合并在一起。此外，我们必须非常清楚和高效地分配我们的工作，这意味着我们两个都没有比另一个做得更多/更少，这保持了项目的公平性，此外，这也意味着我们都知道自己的个人任务是什么，这使我们能够取得有效的进展，而不是浪费时间编写相同的东西。这也适用于在项目结束时完成书面文件，包括用户手册、解释书等。。。
<br />
总之，我个人从完成这个项目的努力中学到了很多，毫无疑问，我在C++方面的能力得到了提高，我对现实生活中编码的理解也得到了加深。总的来说，我对我们所创造的东西感到非常自豪，尽管我们只学习了大约3个月的代码。展望未来，由于编码在现代生活中变得越来越重要，我想继续深入学习c++，甚至可能考虑学习其他编码语言，如python、java和html。
<br />
<br />

## 栗思祺
在编码过程中，我遇到了很多小问题。首先，我的VSCode配置不对，因为只有main.cpp文件会被编译，其他的.cpp文件没有编译。我在网上查了很多资料才找到解决办法，最后我找到了一个使用task.json（在.vscode文件夹里）编译所有文件的方法。

设计类结构也需要一些思考。我们想让类的结构为过滤食堂而优化，所以我们必须确保所有的东西都是标准化的，所以我们可以很容易地得到我们想要的信息。
这就是为什么我们创建了一个单独的基类Building，这样就可以更容易地获得建筑之间的接近性，即使它们不是食堂。食堂类也提供了很多功能，帮助我们更好地过滤食堂的列表。我们做了一个单独的OpenTime类，以便能够只比较OpenTime对象，用于过滤开放时间。
我们的Meal类实际上仍有很多潜力，我们还没有完全使用。我们可以显示更多关于食堂菜的信息，我们的过滤器也可以显示符合过滤器的菜列表，而不仅仅是食堂。
我们没有实现这样的功能其实主要是一个时间问题，但是我们的程序结构已经为此优化了，不需要调整类设计等。配料枚举也使得过滤想要或不想要的配料更加容易，因为有一个统一的类型，不必用字符串来处理，因为字符串在相互比较时经常会有问题。

除此以外，过滤器模块中的解析并不容易。最大的问题是，我需要解析自定义类，而不是像int或string这样的基本类型。解析OpenTime很困难，最后使用正则表达式其实省去了我很多工作。
此外，对于配料输入，我不得不解析一个向量，这需要做一点研究，如何将逗号分隔的字符串解析成一个字符串向量。对于将字符串转换为枚举值，我幸运地找到了magic_enum包，它简化了这个过程。

关于i18n包，我已经知道一个国际化模块背后的逻辑是什么，所以最大的挑战是编写正确的代码并设计所需要的类，然后就需要进行测试和调试。

总而言之，在做这个项目时，我对c++语言的掌握有了明显的提高，我也很喜欢看到我的代码最终能够运行。