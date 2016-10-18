{
  "variables": {
    "src_dir": "src"
  },
  "targets": [
    {
      "default_configuration": "Release",
      "target_name": "eigen",
      "sources": [
        "<!@(find <(src_dir) -name '*.cc')"
      ],
      "include_dirs": [
        "<(src_dir)",
        "<!(node -e \"require('nan')\")",
        "/usr/local/include/eigen3",
        "/usr/include/eigen3"
      ],
      "configurations": {
        "Debug": {
          "defines": [
            "DEBUG",
            "_DEBUG"
          ],
          "cflags_cc": [
            "-Wall",
            "-Wshadow",
            "-Wunreachable-code",
            "-Wno-unknown-pragmas",
            "-std=c++14"
          ],
          "cflags": [
            "-Wall",
            "-Wshadow",
            "-Wunreachable-code",
            "-Wno-unknown-pragmas",
            "-std=c++14"
          ]
        },
        "Release": {
          "defines": [
            "NDEBUG"
          ],
          "cflags_cc": [
            "-Wall",
            "-Wshadow",
            "-Wunreachable-code",
            "-Wno-unknown-pragmas",
            "-std=c++14",
            "-O3",
            "-flto",
            "-funroll-loops"
          ],
          "cflags": [
            "-Wall",
            "-Wshadow",
            "-Wunreachable-code",
            "-Wno-unknown-pragmas",
            "-std=c++14",
            "-O3",
            "-flto",
            "-funroll-loops"
          ]
        }
      },
      "cflags!": [
        "-fno-exceptions",
        "-fno-rtti",
        "-O2",
        "-std=gnu++0x"
      ],
      "cflags_cc!": [
        "-fno-exceptions",
        "-fno-rtti",
        "-O2",
        "-std=gnu++0x"
      ],
      "conditions": [
        [
          "OS=='mac'",
          {
            "xcode_settings": {
              "CLANG_CXX_LANGUAGE_STANDARD": "c++14",
              "MACOSX_DEPLOYMENT_TARGET": "10.11",
              "GCC_ENABLE_CPP_EXCEPTIONS": "YES",
              "GCC_ENABLE_CPP_RTTI": "YES",
              "OTHER_CPLUSPLUSFLAGS": [
                "-stdlib=libc++",
                "-Wcast-qual",
                "-Wdisabled-optimization",
                "-Wdocumentation",
                "-Wextra",
                "-Wextra-semi",
                "-Wfloat-equal",
                "-Wmissing-noreturn",
                "-Wno-covered-switch-default",
                "-Wno-c++98-compat",
                "-Wno-c++98-compat-pedantic",
                "-Wno-newline-eof",
                "-Wold-style-cast",
                "-Wpointer-arith",
                "-Wredundant-decls",
                "-Wreserved-id-macro",
                "-Wswitch",
                "-Wunreachable-code",
                "-Wunused",
                "-Wunused-macros",
                "-Wwrite-strings"
              ],
              "OTHER_LDFLAGS": [
                "-stdlib=libc++"
              ]
            },
            "configurations": {
              "Debug": {
                "xcode_settings": {
                  "GCC_GENERATE_DEBUGGING_SYMBOLS": "YES",
                  "GCC_OPTIMIZATION_LEVEL": "0"
                }
              },
              "Release": {
                "xcode_settings": {
                  "GCC_GENERATE_DEBUGGING_SYMBOLS": "NO",
                  "GCC_OPTIMIZATION_LEVEL": "fast",
                  "OTHER_CPLUSPLUSFLAGS": [
                    "-funroll-loops"
                  ],
                  "OTHER_LDFLAGS": [
                    "-funroll-loops"
                  ]
                }
              }
            }
          }
        ]
      ]
    }
  ]
}
