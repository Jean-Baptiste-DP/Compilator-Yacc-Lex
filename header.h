/* --- Type definition --- */

typedef struct intStack{
    int value;
    struct intStack *next;
}*IntStack;

typedef struct calcSym{
    int value;
    int type;
    char *variable;
}*Symbole;

typedef struct calcTree{
    Symbole symbole;
    struct calcTree *leftChild;
    struct calcTree *rightChild;
}*CalculNb;

typedef struct fctParameters
{
    int calc;
    bool executed;
    int value;
    struct fctParameters *nextParameter;
} *FctParameters;

typedef struct fctRegister
{
    char *name;
    bool executed;
    int value;
    FctParameters parameters;
}*FctRegister;

typedef struct allCalcFct{
    int length;
    int lastElement;
    FctRegister *line;
}*AllCalcFct;

typedef struct VariableStruct
{
    char *name;
    char *type;
    int value;
}*Variable;

typedef struct AllVariables
{
    struct VariableStruct *var;
    struct AllVariables *next;
}*DataStack;

typedef struct data{
    DataStack myData;
}*Data;

typedef struct calcul
{
    CalculNb nb;
    AllCalcFct fct;
}*Calcul;

typedef struct calcLine{
    int length;
    int lastElement;
    Calcul *line;
}*CalcStorage;

/* --- Variable --- */

Variable newVar(char *name, char *type, int value);
void freeVar(Variable var);

/* --- DataStack : Variable storage --- */

DataStack newDataStack();
bool isEmptyStack(DataStack variables);
bool isVarExistStack(DataStack variables, char *name);
Variable getVarStack(DataStack variables, char *name);
DataStack deleteVarStack(DataStack variables, char *name);
DataStack storeVarStack(DataStack variables, Variable var);
void freeDataStack(DataStack variables);

/* --- Data Storage --- */

Data newData();
bool isEmpty(Data variables);
bool isVarExist(Data variables, char *name);
Variable getVar(Data variables, char *name);
void deleteVar(Data variables, char *name);
void storeVar(Data variables, Variable var);
void freeData(Data variables);

/* --- Calcul Symbole --- */

Symbole newSymbole(int type, int val, char *var);
Symbole freeSymbole(Symbole mysym);

/* --- Calcul Tree --- */

CalculNb leafConst(int value);
CalculNb leafVar(char *varName);
CalculNb leafFct(int fctPosition);
CalculNb nodeOperator(int operat, CalculNb lChild, CalculNb rChild);
void freeCalculNb(CalculNb myCalc);
int runCalculNb(CalculNb myCalc, AllCalcFct fct, Data myData);
void incrementFctIndex(CalculNb tree, int num);


/* --- Parameters function storage --- */

FctParameters addParameter(int calc, FctParameters nextPara);
void freeParameter(FctParameters parameter);
char *getCallBack(FctParameters parameter, Data myData, CalcStorage myCalculs);
IntStack getParametersValues(FctParameters parameter);
void parameterExecutionFalse(FctParameters parameter);

/* --- Functions --- */

FctRegister initFct(char *name, FctParameters parameters);
void freeFctRegistered(FctRegister fct);
char *getFctCallBack(FctRegister fct, Data myData, CalcStorage myCalc);

/* -- Storage of calculs functions --- */

AllCalcFct noFctinCalc();
void storeFctCalc(AllCalcFct allFct, FctRegister fct);
char *getCallBackInAll(AllCalcFct allFct, Data myData, CalcStorage myCalc);
void freeAllCalcFct(AllCalcFct allFct);

/* --- One calcul --- */

Calcul newCalc(CalculNb nb, AllCalcFct fct);
void freeCalcul(Calcul calc);
char *getCalcCallBack(Calcul myCalc, Data myData, CalcStorage myCalcStorage);
int runCalcul(Calcul myCalc, Data myData);
Calcul ConstCalc(int constante);
Calcul VarCalc(char *name);
Calcul FctCalc(char *name, FctParameters parameters);
Calcul OpeCalc(int operat, Calcul left, Calcul right);

/* --- All calculs --- */

CalcStorage newCalcStorage();
void storeCalcul(CalcStorage storage, Calcul calc);
Calcul getCalc(CalcStorage storage, int index);
void freeCalcStorage(CalcStorage storage);