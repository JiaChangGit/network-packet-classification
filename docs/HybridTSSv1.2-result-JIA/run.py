import os
import argparse

dir = './'
# os.system('rm *.csv')
parser = argparse.ArgumentParser(description='execute the code')
parser.add_argument('--mode', type=str, default='AllRule', help="run mode[ruleFile Name] [AllRule]")
parser.add_argument('--make', type=bool, default=False, help="rebuild before execute")

args = parser.parse_args()
print(args)


if args.mode == "AllRule":
    os.system('make')
    os.system('rm result.csv')
    ruleType = ['acl','ipc','fw']
    ruleName = [str(i + 1) + '_' for i in range(5)]
    ruleSize = ['1k', '10k', '100k']

    for t in ruleType:
        for s in ruleSize:
            for r in ruleName:
                rule2 = t + r + s
                dir_file = os.path.join(dir, rule2)
                # print(dir_file)
                if not os.path.isfile(dir_file):
                    print('Not exist')
                    continue
                str = './main -r ' + dir + rule2 + ' -p ' + dir + rule2 + '_trace'
                # str = './bin/tool_classifier.exe -m nuevomatch -l -in ./Train/' + rule2 + '.data --trace ./../ruleslwj/' + rule2 + '_trace --parallel 1 --trace-silent --max-subsets 1 --remainder-type tuplemerge --force-remainder-build -v 3'
                print(str)
                os.system(str)
                # x = input('press any key to continue')
                # os.system(str)
                # print(rule2)
else:
    if args.make:
        os.system('make')
    orderStr = './main -r ' + dir + args.mode + ' -p ' + dir + args.mode + '_trace'
    print(orderStr)
    os.system(orderStr)
