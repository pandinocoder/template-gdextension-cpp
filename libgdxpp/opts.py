import argparse
import os
import pathlib

from .platform import Platform

class Opts(argparse.Namespace):
    subcommand: str

    def validate(self) -> void:
        self.__validate__common__()

        match self.subcommand:
            case "build":
                self.__validate__build__()

            case "prepare":
                self.__validate__prepare__()

            case "run":
                self.__validate__run__()

#region Common Options
    verbose: bool

    def __validate__common__(self) -> void:
        pass

#endregion Common Options

#region Build Options

    cores: int
    debug_symbols: bool
    dev_build: bool
    exceptions: bool
    output: pathlib.Path
    platform: Platform
    skip_godot_cpp: bool
    target: str
    use_hot_reload: bool
    use_llvm: bool
    use_mingw: bool
    use_static_cpp: bool

    def __validate__build__(self) -> void:
        if self.platform == None:
            self.platform = Platform.get_current()

        cores = self.cores
        if cores < 1:
            total_cores = os.cpu_count()
            cores = int(max(1, total_cores * 3 / 4))

        process_cores = os.process_cpu_count()
        self.cores = min(cores, process_cores)

        dev_build = self.dev_build

        target = str(self.target).lower()
        match target:
            case "d" |  "dbg" | "debug":
                dev_build = True if dev_build == None else dev_build
                target = "template_debug"

            case "r" | "rel" | "release":
                dev_build = False if dev_build == None else dev_build
                target = "template_release"

            case _:
                dev_build = True if dev_build == None else dev_build
                target = "template_debug"

        self.target = target

        self.dev_build = dev_build

        self.output = self.output.resolve(strict=True)

        if self.use_hot_reload == None:
            self.use_hot_reload = target != "template_release"

        if self.use_static_cpp == None:
            self.use_static_cpp = target == "template_release"

#endregion Build Options

#region Prepare Options

    def __validate__prepare__(self) -> void:
        pass

#endregion Prepare Options

#region Run Options

    editor: bool
    project_path: pathlib.Path

    def __validate__run__(self) -> void:
        self.project_path = self.project_path.resolve(strict=True)

#endregion Run Options