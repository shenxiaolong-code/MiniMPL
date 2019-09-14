当在不同的项目中进行移植时，由于不同的项目可能使用了下面的一些自定义的类型：
when port code between different project, because different project might uses below different items:
1. STL container, e.g. vector, list
2. string
3. smart pointer
4. ASCII or UNICODE
5. ....

所以需要指定这些项目自定义的内容。
1. 使用满足项目实情情况的productSpecialDef.h来替换.\CodeLib\include\MiniMPL\productSpecialDef.h
2. 更新.\CodeLib\include\MiniMPL\libConfig.h中的USE_UNICODE_STRING来指示当前项目使用的是ASCII还是UNICODE
So need to define this different thing.
1. use the yourself productSpecialDef.h to replace .\CodeLib\include\MiniMPL\productSpecialDef.h .
2. libConfig.h might need to be update for ASCII/UNICODE switch [USE_UNICODE_STRING].

注意：
当前的.\CodeLib\include\MiniMPL\productSpecialDef.h中使用的缺省STL命名空间是"std". 
如果实际项目中没有自定义stl库或者使用特殊的STL组件，缺省的productSpecialDef.h不需要更新。
NOTE:
current .\CodeLib\include\MiniMPL\productSpecialDef.h is used for STL "std". 
if your project have not cutomized the STL lib / used yourself STL componment , default productSpecialDef.h is OK and needn't be update. 

例子：
在.\productSpecial\SevenExcellence\目录下有一个SevenExcellence项目中使用的productSpecialDef.h例子。
当在SevenExcellence中使用此库程序时，复制.\productSpecial\SevenExcellence\productSpecialDef.h到.\include\MiniMPL\并且覆盖productSpecialDef.h即可。
Example:
There is one example in .\productSpecial\SevenExcellence\productSpecialDef.h for SevenExcellence project.
when used in project SevenExcellence, copy .\productSpecial\SevenExcellence\productSpecialDef.h into .\include and overwrite existing productSpecialDef.h