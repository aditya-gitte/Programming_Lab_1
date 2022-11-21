import sys

opTable = {}
with open("Optable.txt") as OptableFile:
    lines = [line.rstrip() for line in OptableFile]

for line in lines:
    wordlist = line.split()
    key = wordlist[0]
    wordlist.pop(0)
    opTable[key] = wordlist

registerTable = {}
with open("Registers.txt") as RegisterFile:
    lines = [line.rstrip() for line in RegisterFile]

for line in lines:
    wordlist = line.split()
    registerTable[wordlist[0]] = wordlist[1]

conditionTable = {}
with open("Conditions.txt") as ConditionFile:
    lines = [line.rstrip() for line in ConditionFile]

for line in lines:
    wordlist = line.split()
    conditionTable[wordlist[0]] = wordlist[1]

sourceTable = []
with open("Assembly.txt") as AssemblyFile:
    lines = [line.rstrip() for line in AssemblyFile]

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
for lineList in sourceTable:
    if len(lineList) < 4:
        remainingspaces = 4 - len(lineList)
        for i in range(remainingspaces):
            lineList.append(" ")

intermediateTable = []
poolTable = []
poolTableCounter = []
poolTableHistory = []
symbolTable = {}
literalTable = {}
lc = 0


def ProcessOriginSuffix(str):
    strList = []
    splitCharacter = '+'
    for char in str:
        if char == '-':
            splitCharacter = '-'
            break
    strList = str.split(splitCharacter)
    firstint = int(symbolTable[strList[0]])
    secondint = int(strList[1])
    if splitCharacter=='+':
        return firstint + secondint
    else:
        return firstint - secondint





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

        elif sourceTable[rowIndex][1] == "LTORG":  # handles LTORG
            poolTableCounter.append(len(poolTable))
            loc = int(intermediateTable[rowIndex][1])
            for poolnum in poolTable:
                literalTable[poolnum] = loc
                loc += 1
            nextLocation = str(loc)
            rowNext = [sourceTable[rowIndex + 1], nextLocation]
            intermediateTable.append(rowNext)
            poolTable.clear()

        elif sourceTable[rowIndex][1] == "EQU":  # handles EQU
            symbolTable[sourceTable[rowIndex][0]] = symbolTable[sourceTable[rowIndex][2]]
            rowNext = [sourceTable[rowIndex + 1], intermediateTable[rowIndex][1]]
            intermediateTable.append(rowNext)

        else:  # when the keyword encountered is neither origin or LTORG
            nextLocationIncrement = int(opTable[sourceTable[rowIndex][1]][2])
            nextLocation = str(int(intermediateTable[rowIndex][1]) + nextLocationIncrement)
            rowNext = [sourceTable[rowIndex + 1], nextLocation]
            intermediateTable.append(rowNext)

    if intermediateTable[rowIndex][0][1] == "ORIGIN" or intermediateTable[rowIndex][0][
        1] == "EQU":  # removes the location counter from origin statements
        intermediateTable[rowIndex][1] = " "

print(intermediateTable)
# Second Pass, till now the symbol table and literal table have already been created and the location counter has been,
# updated for every entry in intermediate table,

for key in opTable.keys():  # removed the length of the instruction from opcode table to make it easier to use directly in the intermediate code table
    opTable[key].pop(2)

ltorgCounter = 0  # handling the LTORG
while ltorgCounter < len(poolTableCounter):  # used for handling multiple LTORG statements
    for rowIndex in range(len(intermediateTable)):
        if intermediateTable[rowIndex][0][1] == "LTORG":
            print(f"{ltorgCounter} this is ltorg table")
            print(poolTableCounter[ltorgCounter])
            noOfLiteralToRead = poolTableCounter[ltorgCounter]
            for i in range(
                    noOfLiteralToRead):  # adds 2 rows in intermediate table as two literal have been assigned address at this LTORG
                interRow = [intermediateTable[rowIndex][0], str(literalTable[poolTableHistory[i]])]
                print(f"Added a row at {rowIndex + i}")
                intermediateTable.insert(rowIndex + i + 1, interRow)
            del intermediateTable[rowIndex + i]  # removes the initial LTORG statement
            ltorgCounter += 1
            break

# inverting the key value relation in the literal table dictionary for easier access
invLiteralTable = {}
for k, v in literalTable.items():
    invLiteralTable[v] = k


def KeyPresntInDictionary(dic, key):
    flag = False
    for k in dic.keys():
        if k == key:
            flag = True
            break
    return flag


# adding the remaining data in the intermediate table
for rowIndex in range(len(intermediateTable)):
    if intermediateTable[rowIndex][0][1] == "START":
        intermediateTable[rowIndex].append(opTable["START"])
        intermediateTable[rowIndex].append(f"(C,{intermediateTable[rowIndex][0][2]})")
        intermediateTable[rowIndex].append(" ")
    elif intermediateTable[rowIndex][0][1] == "LTORG":
        intermediateTable[rowIndex].append(opTable["LTORG"])
        intermediateTable[rowIndex].append(f"(C,{invLiteralTable[int(intermediateTable[rowIndex][1])]})")
        intermediateTable[rowIndex].append(" ")
    elif intermediateTable[rowIndex][0][1] == "EQU":
        intermediateTable[rowIndex].append(" ")
        intermediateTable[rowIndex].append(" ")
        intermediateTable[rowIndex].append(" ")
    elif intermediateTable[rowIndex][0][1] == "ORIGIN":
        intermediateTable[rowIndex].append(opTable[intermediateTable[rowIndex][0][1]])
        str = intermediateTable[rowIndex][0][2]
        splitCharacter = '+'
        for char in str:
            if char == '-':
                splitCharacter = '-'
                break
        wordlist = str.split(splitCharacter)
        appendstr = f"(S,{list(symbolTable).index(wordlist[0]) + 1}){splitCharacter}{wordlist[1]})"
        intermediateTable[rowIndex].append(appendstr)
        intermediateTable[rowIndex].append(" ")
    elif intermediateTable[rowIndex][0][1] == "DS":
        intermediateTable[rowIndex].append(opTable[intermediateTable[rowIndex][0][1]])
        intermediateTable[rowIndex].append(f"(C,{intermediateTable[rowIndex][0][2]})")
        intermediateTable[rowIndex].append(" ")
    else:
        intermediateTable[rowIndex].append(opTable[intermediateTable[rowIndex][0][1]])
        operand1 = intermediateTable[rowIndex][0][2]
        if operand1 == " ":
            intermediateTable[rowIndex].append(" ")
        elif operand1 == "AREG" or operand1 == "BREG" or operand1 == "CREG" or operand1 == "DREG":
            intermediateTable[rowIndex].append(registerTable[operand1])
        elif KeyPresntInDictionary(conditionTable, operand1):
            intermediateTable[rowIndex].append(f"(CT,{conditionTable[operand1]})")
        else:  # means that the operand is SYMBOL from the SYMBOL TABLE
            intermediateTable[rowIndex].append(f"(S,{list(symbolTable).index(operand1) + 1})")
        operand2 = intermediateTable[rowIndex][0][3]
        if operand2 == " ":
            intermediateTable[rowIndex].append(" ")
        elif ifLiteral(operand2):
            lit = getLiteral(operand2)
            intermediateTable[rowIndex].append(f"(L,{list(literalTable).index(lit) + 1})")
        elif KeyPresntInDictionary(conditionTable, operand2):
            intermediateTable[rowIndex].append(f"(CT,{conditionTable[operand2]})")
        else:
            intermediateTable[rowIndex].append(f"(S,{list(symbolTable).index(operand2) + 1})")

print("===============================================Printing tables=================================================")

print(f"Register table: {registerTable}")
print(f"Conditions Table: {conditionTable}")
print(f"Intermediate table: {intermediateTable}")
print(f"Symbol Table {symbolTable}")
print(f"Pool Table: {poolTable}")
print(f"Pool History Table: {poolTableHistory}")
print(f"Pool table counter {poolTableCounter}")
print(f"Literal Table: {literalTable}")
print(f"Inverse Literal Table: {invLiteralTable}")
