#!/usr/bin/env python

import os
import sys
import pdb

from glob import glob
from libgdxpp.stdio import *
from pathlib import Path

localEnv = Environment(tools=["default"], PLATFORM="")

opts = Variables(None, ARGUMENTS)
opts.Update(localEnv)

env = localEnv.Clone()

env = SConscript("vendor/godot-cpp/SConstruct", {"env": env})

# Commenting this out because of
# .../ld.exe: .../lib\libstdc++.a(tinfo.o):(.text$_ZNKSt9type_infoeqERKS_+0x0): multiple definition of `std::type_info::operator==(std::type_info const&) const'; extensions\gdwz\src\wz\wzcommon.o:.../include/c++/14.2.0/typeinfo:193: first defined here
# collect2.exe: error: ld returned 1 exit status
# env.Append(CXXFLAGS=["-std=c++23"])

# print("Dumping environment: ", env.Dump())

# pdb.set_trace()

# For reference:
# - CCFLAGS are compilation flags shared between C and C++
# - CFLAGS are for C-specific compilation flags
# - CXXFLAGS are for C++-specific compilation flags
# - CPPFLAGS are for pre-processor flags
# - CPPDEFINES are for pre-processor defines
# - LINKFLAGS are for linking flags

# Add targets for all detected extensions
for extension_path in glob("extensions/*/*.gdextension"):
    extension_dir_path = Path(extension_path).parent
    extension_name = extension_dir_path.stem

    extension_src_path = extension_dir_path.joinpath('src').resolve()
    extension_src_path_str = str(extension_src_path)
    extension_bin_path = extension_dir_path.joinpath('bin')

    # Find all .cpp source files
    env.Append(CPPPATH=[
        extension_src_path_str,
    ])

    glob_string_gdextension_root = extension_dir_path.joinpath('*.gdextension*')
    extension_metadata = Glob(glob_string_gdextension_root)

    extension_sources = []

    for root, dirs, files in os.walk(str(extension_dir_path)):
        for dir in dirs:
            dir_path = Path(os.path.join(root, dir))
            dir_path_resolved = str(dir_path.resolve())

            glob_string_gdextension = os.path.join(dir_path_resolved, '*.gdextension*')
            extension_metadata += Glob(glob_string_gdextension)

            in_srcdir = dir_path_resolved.startswith(extension_src_path_str)
            if in_srcdir:
                glob_string_subdir_sources_cxx = os.path.join(dir_path_resolved, "*.c*")
                extension_sources += Glob(glob_string_subdir_sources_cxx)

    # Add documentation
    extension_doc_path = extension_dir_path.joinpath('doc_classes')
    extension_doc_glob_string = extension_doc_path.joinpath('*.xml')
    if env["target"] in ["editor", "template_debug"]:
        try:
            doc_data_path = extension_src_path.joinpath("gen", "doc_data.gen.cpp")
            doc_data = env.GodotCPPDocData(doc_data_path, source=Glob(extension_doc_glob_string))
            for doc_data_entry in doc_data:
                if doc_data_entry not in extension_sources:
                    extension_sources.append(doc_data_entry)
        except AttributeError:
            print_error("Not including class reference as we're targeting a pre-4.3 baseline.")

    extension_metadata_count = len(extension_metadata)
    if extension_metadata_count > 0:
        print_info('\tFound %d metadata files for %s:\n%s' % (
            extension_metadata_count,
            extension_name,
            os.linesep.join(['\t  - %s' % metadatum for metadatum in extension_metadata])
        ), dim=True)
    else:
        print_warning('\tNo metadata files found for %s' % (
            extension_name
        ))

    extension_sources_count = len(extension_sources)
    if extension_sources_count > 0:
        print_info('\tFound %d source files for %s:\n%s' % (
            extension_sources_count,
            extension_name,
            os.linesep.join(['\t  - %s' % source for source in extension_sources])
        ), dim=True)
    else:
        print_error('\tNo source files found for %s' % (
            extension_name
        ))

    # Create the library target (e.g. libexample.linux.debug.x86_64.so).
    debug_or_release = "release" if env["target"] == "template_release" else "template_debug"

    extension_library_name = "{}/bin/{}{}.{}.{}.{}{}".format(
        extension_dir_path,
        env.subst('$SHLIBPREFIX'),
        extension_name,
        env["platform"],
        debug_or_release,
        env["arch"],
        env["SHLIBSUFFIX"],
    )

    if env["platform"] == "macos":
        extension_library_name = "{0}/bin/lib{1}.{2}.{3}.framework/{1}.{2}.{3}".format(
            extension_dir_path,
            extension_name,
            env["platform"],
            debug_or_release,
        )

    extension_library = env.SharedLibrary(
        extension_library_name,
        source=extension_sources,
    )

    extension_install_path = "project/extensions/{}".format(extension_name)
    extension_install_bin_path = "{}/bin".format(extension_install_path)

    print_notice('Installing metadata files to %s...' % extension_install_path, dim=True)
    print_notice('Installing binaries to %s... %s' % (extension_install_bin_path, extension_library), dim=True)
    extension_install = [
        env.Install(
            extension_install_path,
            extension_metadata,
        ),
        env.Install(
            extension_install_bin_path,
            extension_library,
        )
    ]

    default_args = [
        extension_library,
        extension_install
    ]
    Default(*default_args)

from SCons import __version__ as scons_raw_version
scons_ver = env._get_major_minor_revision(scons_raw_version)
if scons_ver >= (4, 0, 0):
  env.Tool("compilation_db")
  cdb = env.CompilationDatabase()
  env.Alias("compiledb", cdb)
  Default(cdb)