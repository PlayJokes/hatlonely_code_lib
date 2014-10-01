#!/usr/bin/env python
#!coding: utf-8

import sys
import argparse

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('-n', '--name', default='hatlonely', help='your name');
    parser.add_argument('-e', '--email', default='hatlonely@gmail.com', help='your email address')
    parser.add_argument('-p', '--passwd', required=True, help='your passwd')
    parser.add_argument('-g', '--gender', choices=['M', 'F'], required=True, help='gender')
    args = parser.parse_args(sys.argv[1:])
    print('name: ' + args.name)
    print('email: ' + args.email)
    print('gender: ' + args.gender)


if __name__ == '__main__':
    main()
