#!/usr/bin/env python3
###
# This file is part of the Susci project, an ultra lightweight general purpose
# operating system aimed at devices without an MMU module and with very little
# RAM memory.
# 
# It is released under the terms of the MIT license, you can use Susca in your
# projects, you just need to mention it in the documentation, manual or other 
# such place.
# 
# Author: Cixo
#
#
# This is the installation manager of the Susci operating system. Lets you 
# install the package so that it can be included like the standard library with
# <>, instead of copying each project to directory and appending with quotes.
###


import subprocess
import sys
import os


SUSCI_SOURCE_DIR = './Source'

def run_command(command) -> str:
    result = subprocess.run(
        command, text = True, shell = True, capture_output = True
    )

    return result.stderr + '\n' + result.stdout

def get_gcc_include_path() -> str:
    command = run_command('avr-gcc -E -Wp,-v -xc /dev/null')

    start_text = '#include <...> search starts here:'
    end_text = 'End of search list.'

    path = command[
        command.find(start_text) + len(start_text) + 1:
        command.find(end_text) - 1
    ].split('\n')

    return (path[-1] + '/')[path[-1].find('/'):]

def is_installed(target_dir):
    return os.path.exists(target_dir + '/Susci')

def get_version(susci_dir):
    include_content = run_command('cat ' + susci_dir + '/Kernel.h')

    version_flag = 'SUSCI_VERSION'
    revision_flag = 'SUSCI_REVISION'

    version = include_content[
        include_content.find(version_flag) + len(version_flag) + 1:
    ]
    version = version[:version.find('\n')]

    revision = include_content[
        include_content.find(revision_flag) + len(revision_flag) + 1:
    ]
    revision = revision[:revision.find('\n')]

    return version, revision

def install_it(susci_dir, gcc_include_path):
    return run_command('cp ' + susci_dir + '/ ' + gcc_include_path + '/Susci -R')

def remove_it(gcc_include_path):
    return run_command('rm -R ' + gcc_include_path + '/Susci')


def usermode_remove():
    if not is_installed(get_gcc_include_path()):
        print(" * Susci is not installed, it cannot be uninstalled!")
        exit()

    print(" * Deleting unnecessary files (requires script to be run as root)...")
    print(remove_it(get_gcc_include_path()))

    if not is_installed(get_gcc_include_path()):
        print(" * Everything went well!")
    else:
        print(" * Something's wrong, I can feel it!")

def usermode_install():
    if is_installed(get_gcc_include_path()):
        print(" * Susci is already installed!")
        exit()

    print(" * Copying files (requires script to be run as root)...")
    print(install_it(SUSCI_SOURCE_DIR, get_gcc_include_path()))
    
    if is_installed(get_gcc_include_path()):
        print(" * Everything went well!")
        print(" * May need to change permissions (chmod 755 " + get_gcc_include_path() + " -R)")
    else:
        print(" * Something's wrong, I can feel it!")


if '-h' in sys.argv or '--help' in sys.argv:
    print('Welcome to the Susci version manager help. This script allows you to:')
    print(" * -v, --version \t Shows the version of the system that is installed")
    print(" * -h, --help \t\t Shows this help screen")
    print(" * -i, --install \t Installs system for avr-gcc (requires root)")
    print(" * -r, --remove \t Uninstalls system for avr-gcc (requires root)")
    print(" * -u, --update \t Updates system for avr-gcc (requires root)")
    print(" * -v, --version \t Shows version of Susci")
    exit()


elif '-i' in sys.argv or '--install' in sys.argv:
    print("The installation begins...")
    usermode_install()


elif '-r' in sys.argv or '--remove' in sys.argv:
    print("The uninstallation begins...")
    usermode_remove()


elif '-u' in sys.argv or '--update' in sys.argv:
    print("The update has started...")
    usermode_remove()
    usermode_install()


elif '-v' in sys.argv or '--version' in sys.argv:
    print("Version of Susci:")

    if is_installed(get_gcc_include_path()):
        print(" * Installed: " + str(get_version(get_gcc_include_path() + '/Susci')[0]) + ' rev: ' + str(get_version(get_gcc_include_path() + '/Susci')[1]))
    else:
        print(" * Susci is not installed!")

    print(" * In installer: " + str(get_version(SUSCI_SOURCE_DIR)[0]) + ' rev: ' + str(get_version(SUSCI_SOURCE_DIR)[1]))


else:
    print("You need to give some action to perform, if you don't know how, use -h or --help")