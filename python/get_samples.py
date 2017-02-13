#!/usr/bin/env python
"""
Get samples list. 
"""

__author__ = "SHI Xin <shixin@ihep.ac.cn>"
__copyright__ = "Copyright (c) SHI Xin"
__created__ = "[2016-05-30 Mon 09:19]"

import sys
import os
from tools import save_list_into_file, group_files_by_size


def usage():
    sys.stdout.write('''
NAME
    get_samples.py 

SYNOPSIS

    ./get_samples.py  input_dir output_file [size]
    ./get_samples.py  3890MeV input_dir output_file [size]
AUTHOR 
    SHI Xin <shixin@ihep.ac.cn> 
    YM SU 

DATE
    June 2016 
\n''')

    
def main():
    args = sys.argv[1:]
    if len(args) < 2:
        return usage()
    
    if args[0] == '3890MeV': 
        get_3890MeV(args[1],args[2],args[3])  
        return 

    src = args[0]
    dst = args[1]
    sys.stdout.write('Scanning %s...\n' %src)

    file_list = []
    for root, dirs, files in os.walk(src):
        for f in files:
            file_list.append(os.path.join(root, f))

    if len(args) == 2:
        save_list_into_file(file_list, dst)
        return
    
    if len(args) == 3:
        size = args[2]
        sys.stdout.write('Size limit per list: %s\n' %size)
        groups = group_files_by_size(file_list, size)
        path, name = os.path.split(dst)
        dst_com = name.split('.')[0] 
        dst_ext = name.split('.')[1]
        n = 0 
        for file_list in groups:
            n = n+1 
            new_dst = os.path.join(path, '%s_%s-%s.%s' %
                                   (dst_com, size, n, dst_ext))
            save_list_into_file(file_list, new_dst)
        
def get_3890MeV(input_dir,output_file,size): 
    src = input_dir
    dst = output_file
    sys.stdout.write('Scanning %s...\n' %src)

    file_list = []
    run_list = []
    for run in range(34028,34037):
        run_list.append(run)

    for root, dirs, files in os.walk(src):
        for f in files:
            for c in run_list:
                if str(c) in str(f):
                    file_list.append(os.path.join(root, f))

    print len(file_list) 
    sys.stdout.write('Size limit per list: %s\n' %size)
    groups = group_files_by_size(file_list, size)
    path, name = os.path.split(dst)
    dst_com = name.split('.')[0] 
    dst_ext = name.split('.')[1]
    n = 0 
    for file_list in groups:
        n = n+1 
        new_dst = os.path.join(path, '%s_%s-%s.%s' %
                               (dst_com, size, n, dst_ext))
        save_list_into_file(file_list, new_dst)

if __name__ == '__main__':
    main()
