# Arbitrium
CS:GO Open Source Cheating Software written in C++ directed towards usage on the Windows 10 (x86_64) platform. Will also be used as a reverse-engineering 'sandbox' at times with ability to experiment with under-development methods by passing compiler directives.

# Prerequisites
Arbitrium is maintained with [Visual Studio 2019 (Community version)](https://visualstudio.microsoft.com/vs/community/), with the latest stable version of both MSVC (bundled) and Windows SDK (available in extras installer). These are deemed to change, though, with the evolution of the project.

# Building from source
First, download the source code from the repository, either by [downloading by your browser](https://github.com/cristeigabriel/Arbitrium/archive/main.zip), or by using Git

```git clone https://github.com/cristeigabriel/Arbitrium.git```

Either should create a folder 'Arbitrium' which contains the Git page tree.

Once we have this done, proceed to open the ```Arbitrium.sln``` file, change your build settings to ```Debug | x86``` or ```Release | x86``` depending on what you're planning to do, then press F5. This'll proceed to build the static libraries required for the principal project of the solution [Arbitrium] then proceed to build a DLL with the aforementioned linked.

**! You don't need to share the '.lib' files when you wish to send the cheat binary to someone. These are built just to be ultimately linked. Consider them compilation dependencies.``` 

# Contributing
Contributions are welcome under the form of [pull requests](https://github.com/cristeigabriel/Arbitrium/pulls), you can do one if you consider that something could be done in a better way, if you want to contribute in regards of the overall functionality, or whatever you deem fit. If you're currently undecided on whether you should, or not, open a pull request, you can refer to the [issues](https://github.com/cristeigabriel/Arbitrium/issues) page. Furthermore, you can also contribute by noting out issues and [reporting them](https://github.com/cristeigabriel/Arbitrium/issues).

# Injecting
Arbitrium is prepared to inject under any well known method, but if noticed otherwise, you can open an [issue](https://github.com/cristeigabriel/Arbitrium/issues) or proceed to create a [pull request](https://github.com/cristeigabriel/Arbitrium/pulls) considering you have managed to solve an issue preventing the aforementioned. This means, Arbitrium should work with your injector of preference, to which you only need to pass your DLL.

# License
[WTFPL v2](https://github.com/cristeigabriel/Arbitrium/blob/main/LICENSE)
