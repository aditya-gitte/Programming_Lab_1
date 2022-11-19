import sys

opTable = {}
with open("Optable.txt") as OptableFile:
    lines = [line.rstrip() for line in OptableFile]

for line in lines:
    wordlist = line.split()
    key = wordlist[0]
    wordlist.pop(0)
    opTable[key] = wordlist

sourceTable = []
with open("Assembly.txt") as AssemblyFile:
    lines = [line.rstrip() for line in AssemblyFile]
    print(lines)
for line in lines:
    row = []
    if line[0] == ' ':
        row.append(" ")
        remlist = line[1:].split()
        for item in remlist:
            row.append(item)
    else:
        wordlist = line.split()
        for word in wordlist:
            row.append(word)
    sourceTable.append(row)

intermediateTable = []
poolTable = []
poolTableCounter = []
poolTableHistory = []
symbolTable = {}
literalTable = {}
lc = 0


def ProcessOriginSuffix(str):
    strList = []
    strList = str.split('+')
    firstint = int(symbolTable[strList[0]])
    secondint = int(strList[1])
    return firstint + secondint


def ifLiteral(str):
    if str[0] == "=":
        return True


def getLiteral(str):
    wordlist = []
    wordlist = str.split("'")
    return wordlist[1]


for rowIndex in range(len(sourceTable)):
    if rowIndex == 0:  # validates start keyword and enters the location counter for the next row
        if sourceTable[0][1] == "START":
            lc = sourceTable[0][2]
            row0 = [sourceTable[0], " "]
            intermediateTable.append(row0)
            row1 = [sourceTable[1], lc]
            intermediateTable.append(row1)
            continue
        else:
            sys.exit("Error, START KEYWORD not found")

    if sourceTable[rowIndex][0] != " ":  # if label is present adds it to the label table
        symbolTable[sourceTable[rowIndex][0]] = intermediateTable[rowIndex][1]

    if len(sourceTable[rowIndex]) > 3:  # if literal present add it to the literal table (handles literal duplication)
        if ifLiteral(sourceTable[rowIndex][3]):
            flag = False
            for poolnum in poolTableHistory:
                if poolnum == getLiteral(sourceTable[rowIndex][3]):
                    flag = True
            if not flag:
                poolTable.append(getLiteral(sourceTable[rowIndex][3]))
                poolTableHistory.append(getLiteral(sourceTable[rowIndex][3]))

    if (rowIndex + 1) < len(sourceTable):  # checks if the next row exists or not
        if sourceTable[rowIndex][1] == "ORIGIN":
            nextLocationIncrement = ProcessOriginSuffix(sourceTable[rowIndex][2])
            nextLocation = str(nextLocationIncrement)
            rowNext = [sourceTable[rowIndex + 1], nextLocation]
            intermediateTable.append(rowNext)

        elif sourceTable[rowIndex][1] == "LTORG":
            poolTableCounter.append(len(poolTable))
            loc = int(intermediateTable[rowIndex][1])
            for poolnum in poolTable:
                literalTable[poolnum] = loc
                loc += 1
            nextLocation = str(loc + 1)
            rowNext = [sourceTable[rowIndex + 1], nextLocation]
            intermediateTable.append(rowNext)
            poolTable.clear()




        else:
            nextLocationIncrement = int(opTable[sourceTable[rowIndex][1]][2])
            nextLocation = str(int(intermediateTable[rowIndex][1]) + nextLocationIncrement)
            rowNext = [sourceTable[rowIndex + 1], nextLocation]
            intermediateTable.append(rowNext)

# for rowIndex in range(len(intermediateTable)):


print(intermediateTable)
print(symbolTable)
print(poolTable)
print(poolTableHistory)
print(poolTableCounter)
