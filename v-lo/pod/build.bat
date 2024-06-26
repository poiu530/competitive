@echo off
if not exist build mkdir build

if "%1" == "unit" (
    clang++ -std=c++20 -O0 -g -o build\unit.exe unit.cpp

    echo ==========================
    echo Unit Tests Output
    echo:

    call build\unit.exe
) else (
    if "%1" == "release" (
        clang++ -std=c++20 -o build\pod.exe pod.cpp

        call build\pod.exe < test1.txt && echo:
        call build\pod.exe < test2.txt && echo:
        call build\pod.exe < test3.txt && echo:
        call build\pod.exe < test4.txt && echo:
        call build\pod.exe < test_1000_12_rng.txt && echo:
        call build\pod.exe < test_1000_50_same.txt && echo:
        call build\pod.exe < test_1000_100_rng.txt && echo:
        call build\pod.exe < test_1000_1_rng.txt && echo:

        clang++ -std=c++20 -o build\binary.exe binary.cpp

        echo BINARY:

        call build\binary.exe < test1.txt && echo:
        call build\binary.exe < test2.txt && echo:
        call build\binary.exe < test3.txt && echo:
        call build\binary.exe < test4.txt && echo:
        call build\binary.exe < test_1000_12_rng.txt && echo:
        call build\binary.exe < test_1000_50_same.txt && echo:
        call build\binary.exe < test_1000_100_rng.txt && echo:
        call build\binary.exe < test_1000_1_rng.txt && echo:

    ) else (
        clang++ -std=c++20 -DPOD_DEBUG -g -o build\pod.exe pod.cpp

        echo ==========================
        echo Old Tests Output
        echo:

        call build\pod.exe test1.txt && echo:
        call build\pod.exe test2.txt && echo:
        call build\pod.exe test3.txt && echo:
        call build\pod.exe test4.txt && echo:
    )
)
