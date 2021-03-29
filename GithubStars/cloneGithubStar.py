#!/bin/python3
import requests
import argparse
import getpass

# based on https://github.com/filosfino/inherit-github-account/blob/master/main.py

GITHUB_API_PROXY = 'https://api.github.com'


def parse_command_line():
    parser = argparse.ArgumentParser(
        description='Follow who he follow, star what he star',
        formatter_class=argparse.RawTextHelpFormatter,
    )
    parser.add_argument('-a', '--auth',
                        metavar='USERNAME',
                        help='your github account username')
    parser.add_argument('target',
                        metavar='TARGET',
                        help='the target you want to copy')

    args = parser.parse_args()

    password = getpass.getpass('Enter your Github account password: ') if args.auth else None
    return args.auth, password, args.target



def star_him(s, target):
    print('>> Starring ...')
    i = 1
    while(True) :
        resp = s.get(GITHUB_API_PROXY + '/users/%s/starred?page=%d&per_page=100' % (target,i) )
        arraylen = len(resp.json())
        if(arraylen == 0):
            break
        itemcnt = 0
        print('NOW starring page %d' % i)
        starred_list = [repo['full_name'] for repo in resp.json()]
        for repo in starred_list:
            if USERNAME:
                s.put(GITHUB_API_PROXY + '/user/starred/%s' % repo)
            print(('[%d/%d] ' % (itemcnt , arraylen)) + repo)
            itemcnt = itemcnt + 1
        i = i + 1
    if USERNAME:
        print('>> starring done\n')

def main():
    s = requests.Session()
    if USERNAME and PASSWORD:
        s.auth = (USERNAME, PASSWORD)

    star_him(s, TARGET)

if __name__ == '__main__':
    USERNAME, PASSWORD, TARGET = parse_command_line()
    main()
