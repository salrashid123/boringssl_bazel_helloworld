
load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")


# http_archive(
#     name = "boringssl",
#     sha256 = "d1700e0455f5f918f8a85ff3ce6cd684d05c766200ba6bdb18c77d5dcadc05a1",
#     strip_prefix = "boringssl-060e9a583976e73d1ea8b2bfe8b9cab33c62fa17",
#     urls = [
#         "https://github.com/google/boringssl/archive/060e9a583976e73d1ea8b2bfe8b9cab33c62fa17.tar.gz",
#     ],
# )


http_archive(
    name = "boringssl",  # Must match upstream workspace name.
    # Gitiles creates gzip files with an embedded timestamp, so we cannot use
    # sha256 to validate the archives.  We must rely on the commit hash and
    # https. Commits must come from the master-with-bazel branch.
    urls = ["https://github.com/google/boringssl/archive/master-with-bazel.zip"],
    strip_prefix = "boringssl-master-with-bazel",
)