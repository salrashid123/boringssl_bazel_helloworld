load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "bssl_lib",
    srcs = ["utils.cc"],
    hdrs = ["utils.h"],
    visibility = ["//main:__pkg__"],
    deps = [
        "@boringssl//:ssl",
    ], 
)
