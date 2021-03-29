#!/bin/python3
import requests
import argparse
import getpass

GITHUB_API_PROXY = 'https://api.github.com'

def parse_command_line():
    parser = argparse.ArgumentParser(
        description='Follow who he follow, star what he star',
        formatter_class=argparse.RawTextHelpFormatter,
    )
    parser.add_argument('-a', '--auth',
                        metavar='USERNAME',
                        help='your github account username')

    args = parser.parse_args()

    password = getpass.getpass('Enter your Github account password: ') if args.auth else None
    return args.auth, password



def unStarAll(s, target):
    print('>> UnStarring ...')
    while(True) :
        resp = s.get(GITHUB_API_PROXY + '/users/%s/starred?page=1&per_page=100' % target )
        arraylen = len(resp.json())
        if(arraylen == 0):
            break
        itemcnt = 0
        print('--------- unstarring new page ---------')
        starred_list = [repo['full_name'] for repo in resp.json()]
        for repo in starred_list:
            if USERNAME:
                s.delete(GITHUB_API_PROXY + '/user/starred/%s' % repo)
            print(('[%d/%d] ' % (itemcnt , arraylen)) + repo)
            itemcnt = itemcnt + 1
    if USERNAME:
        print('>> UnStarring done\n')

def main():
    s = requests.Session()
    if USERNAME and PASSWORD:
        s.auth = (USERNAME, PASSWORD)

    unStarAll(s, USERNAME)

if __name__ == '__main__':
    USERNAME, PASSWORD = parse_command_line()
    main()
