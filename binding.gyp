{
    "variables": {
        "sdk_dir": "deps/gog_sdk",
        "target_dir": "build/lib"
    },
  "targets": [
    {
      "target_name": "napi_sample",
      "sources": [ ],
      "cflags!": [ "-fno-exceptions" ],
      "cflags_cc!": [ "-fno-exceptions" ],
      "defines": [ "NAPI_DISABLE_CPP_EXCEPTIONS",
                "NODE_ADDON_API_DISABLE_DEPRECATED" ],
      "include_dirs": [
        "<!@(node -p \"require('node-addon-api').include\")",
                "<(sdk_dir)/Include"
      ],
      "conditions": [
        ['OS=="win"', {
          "sources": [ "src/exports.cc", "src/test.cc", "src/test.h" ],
        }]
      ],
      'link_settings': {
                'libraries': [
                    # 'deps/gog_sdk/Libraries/Galaxy64.lib',
                    # 'deps/gog_sdk/Libraries/Galaxy64.dll',
                ],
                'library_dirs': [
                    '-l..<(sdk_dir)/Libraries',
                ],
            },
            "xcode_settings": {
                "GCC_ENABLE_CPP_EXCEPTIONS": "YES",
                "CLANG_CXX_LIBRARY": "libc++",
                "MACOSX_DEPLOYMENT_TARGET": "10.7"
            },
            "msvs_settings": {
                "VCCLCompilerTool": {
                    "ExceptionHandling": 1
                }
            },
    },
    {
            "target_name": "copy_binary",
            "dependencies": ["napi_sample"],
            "type": "none",
            "copies": [
                {
                    "destination": "<(module_root_dir)/<(target_dir)",
                    "files": [
                        "<(sdk_dir)/Libraries/Galaxy64.dll",
                        "<(sdk_dir)/Libraries/Galaxy64.lib",
                        "<(module_root_dir)/build/Release/napi_sample.node"
                    ]
                },
            ],
        }
  ]
}
