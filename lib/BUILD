load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "bssl_lib",
    srcs = ["base64.cc"],
    hdrs = ["base64.h"],
    visibility = ["//main:__pkg__"],
    deps = [
        "@boringssl//:ssl",
    ], 
)
