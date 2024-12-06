# LearnOpenGL学习代码

## 项目环境

- cmake 3.29.1
- vcpkg 2024-10-18
- IDE: 自己想用啥用啥

## 三方库安装

vcpkg几乎能免去大部分在三方库安装花掉的时间

```bash
vcpkg install fmt
vcpkg install glfw
vcpkg install glad
vcpkg install stm
```
安装好三方库后通过cmake调用就完事儿了