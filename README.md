# Qt5
`2018.09.08 by jianfeng`

## 关于在Windows下中文显示的问题说明
`环境： QT5.11.1  MSVC2015 32bit`
- windows下的utf-8 本质上是utf-8 BOM
    - [解决方法--步骤]
        1. 工具->选项->行为
            - 文件编码：UTF-8
            - UTF-8 BOM:如果编码是UTF-8则添加
        2. 在**头文件**中加入该声明：
            - #pragma execution_character_set("utf-8")

## 练习目录路径
- 001_WinApp
    > 初次理解Qt界面机制
- 002_login
    > 在主界面前有个登陆界面
    1. 在该项目上添加了布局管理器等的功能
        - ` 布局管理器 `
        - Vertical Layout（垂直布局管理器）
            > 用于自动垂直排列，可水平拉伸
        - 分裂器垂直布局
            > 拉伸的时候，会纵向变大
        - 栅格布局
            > 界面上的内容会填充中央区域，程序运行之后，诸如TextEdit会随着拉伸而变化，保持中央区域填充。
        （若在栅格布局下，上述分裂器的内容也会随之变换）
- 003_login2
    > 无*.ui文件，纯代码编写
- 004_MainApp
    > 菜单项目和ICON的添加
- 005_MyEvent
    > .

# 小项目路径
- TextEdit
    > 简易记事本功能实现