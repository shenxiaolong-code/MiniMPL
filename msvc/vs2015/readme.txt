if refer project in this solution from external path, need to do :

1. add $(solutionName)_setting.props file in .sln directory
   property file "msvc\vs2015\properties_sheet\general_setting\path_setting.props" will search&load it automatically.
   e.g.  similiar file "Core_vs2015_setting.props"

2. define macro variable in file "$(solutionName)_setting.props" in page "Common Properties | User Macros"
   variable name  : CorePath
   variable value : <sources's parent path> , e.g. D:\work\Projects\Core
   check the option "Set this macro as an environment variable in the build environment" when creating the variable.
