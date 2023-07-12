//
// Created by duama on 11.06.2023.
//

#include <cassert>
#include <iostream>
#include "../src/MatrixStorage.h"
#include "../src/Utilities.h"
#include "../src/Exceptions/StorageException.h"
#include "../src/Exceptions/OperationException.h"
#include "../src/Operations/AdditionOperation.h"
#include "../src/Operations/SubtractionOperation.h"
#include "../src/Operations/ExponentiationOperation.h"
#include "../src/Operations/InversionOperation.h"
#include "../src/Operations/GaussEliminationOperation.h"
#include "../src/Operations/JoiningDownOperation.h"
#include "../src/Operations/JoiningRightOperation.h"
#include "../src/Operations/MultiplicationOperation.h"
#include "../src/Operations/MultiplicationNumberOperation.h"
#include "../src/Operations/TransposeOperation.h"
#include "../src/Operations/TrimmingOperation.h"

#define Matrix std::vector<std::vector<double>>


bool checkVectors(Matrix &a, Matrix &b) {
    if (a.size() != b.size()) return false;

    for (size_t i = 0; i < a.size(); ++i) {
        if (a[i].size() != b[i].size()) return false;
        for (size_t j = 0; j < a[i].size(); ++j) {
            if (a[i][j] != b[i][j]) return false;
        }
    }
    return true;
}

void printVector(Matrix &a) {
    for (auto &elem : a) {
        for (auto &e : elem)
            std::cout << e << " ";
        std::cout << std::endl;
    }
}

int main() {
    Utilities utilities;
    auto someelements = Matrix{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    auto matrix = utilities.createMatrix(someelements);
    MatrixStorage storage;
    storage.addMatrix("somename", matrix);

    auto result = storage.getAllMatrices();
    assert(result.size() == 1);

    auto new_result = storage.getMatrix("somename");

    assert(new_result == matrix);

    someelements = Matrix{{4, 5, 6}, {1, 2, 3}, {1, 2, 3}, {4, 5, 6}};
    auto matrix2 = utilities.createMatrix(someelements);
    storage.addMatrix("matrix2", matrix2);

    result = storage.getAllMatrices();
    assert(result.size() == 2);

    storage.removeAllMatrices();

    try {
        result = storage.getAllMatrices();
        assert(1 == 0);
    } catch (StorageException &e) {
        assert(0 == 0);
    } catch (...) {
        assert("Wrong exception" == 0);
    }

    storage.addMatrix("name", matrix);
    storage.addMatrix("onemore", matrix2);

    result = storage.getAllMatrices();

    assert(result.size() == 2);
    storage.removeMatrix("name");

    result = storage.getAllMatrices();
    assert(result.size() == 1);

    try {
        storage.removeMatrix("wrongname");
        assert(0 == 1);
    } catch (StorageException &e) {
        assert(0 == 0);
    } catch (...) {
        assert("Caught wrong exception" == 0);
    }

    // -----------

    assert(utilities.checkName("sometestname"));
    assert(!utilities.checkName(""));
    assert(!utilities.checkName("1testname"));
    assert(!utilities.checkName("add"));
    assert(!utilities.checkName(";;"));

    // -----------

    assert(matrix->numCols() == 3);
    assert(matrix->numRows() == 3);
    assert(matrix2->numRows() == 4);
    assert(matrix2->numCols() == 3);

    auto identityElements = Matrix{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    auto sparseElements = Matrix{{0, 0, 0, 0}, {0, 0, 1, 5}, {4, 6, 3, 2}, {4, 5, 6, 7}};
    auto denseElements = Matrix{{7, 4, 9}, {0, 6, -3}, {4, -10, -4}};

    auto IMatrix = utilities.createMatrix(identityElements);
    auto SMatrix = utilities.createMatrix(sparseElements);
    auto DMatrix = utilities.createMatrix(denseElements);

    assert(IMatrix->numRows() == 3 && IMatrix->numCols() == 3);
    assert(SMatrix->numRows() == 4 && SMatrix->numCols() == 4);
    assert(DMatrix->numRows() == 3 && DMatrix->numCols() == 3);

    assert(IMatrix->determinant() == 1);
    assert(IMatrix->rank() == IMatrix->numCols());
    assert(IMatrix->rank() == IMatrix->numRows());

    assert(SMatrix->rank() == 3);
    assert(SMatrix->determinant() == 0);

    assert(DMatrix->rank() == 3);
    assert(DMatrix->determinant() == -642);

    assert(IMatrix->getVal(0, 0) == 1 && IMatrix->getVal(1, 1) == 1 && IMatrix->getVal(2, 2) == 1);
    assert(IMatrix->getVal(1, 0) == 0 && IMatrix->getVal(2, 1) == 0 && IMatrix->getVal(2, 0) == 0);

    assert(SMatrix->getVal(1, 2) == 1 && SMatrix->getVal(3, 2) == 6 && SMatrix->getVal(1, 0) == 0);

    assert(DMatrix->getVal(0, 0) == 7 && DMatrix->getVal(1, 2) == -3 && DMatrix->getVal(2, 1) == -10);


    auto addoperation = AdditionOperation(DMatrix, IMatrix).execute();
    auto checkElems = Matrix{{8, 4, 9}, {0, 7, -3}, {4, -10, -3}};
    assert(checkVectors(addoperation, checkElems));

    try {
        auto addoperationfail = AdditionOperation(DMatrix, SMatrix).execute();
        assert(0 == 1);
    } catch (OperationException &e) {
        assert(1 == 1);
    } catch (...) {
        assert("Wrong exception" == 0);
    }


    auto suboperation = SubtractionOperation(IMatrix, DMatrix).execute();
    checkElems = Matrix{{-6, -4, -9}, {0, -5, 3}, {-4, 10, 5}};
    assert(checkVectors(suboperation, checkElems));

    try {
        auto suboperationfail = SubtractionOperation(DMatrix, SMatrix).execute();
        assert(0 == 1);
    } catch (OperationException &e) {
        assert(1 == 1);
    } catch (...) {
        assert("Wrong exception" == 0);
    }


    auto expoperation = ExponentiationOperation(SMatrix, 3).execute();
    checkElems = Matrix{{0, 0, 0, 0}, {280, 383, 352, 480}, {308, 412, 409, 544}, {604, 820, 782, 1087}};
    assert(checkVectors(expoperation, checkElems));

    try {
        auto expoperationfail = ExponentiationOperation(matrix2, 2).execute();
        assert(0 == 1);
    } catch (OperationException &e) {
        assert(1 == 1);
    } catch (...) {
        assert("Wrong exception" == 0);
    }

    auto matrix3Elems = Matrix{{1, 2}, {3, 5}};
    auto matrix4Elems = Matrix{{3, 6}, {2, 4}};

    auto matrix3 = utilities.createMatrix(matrix3Elems);
    auto matrix4 = utilities.createMatrix(matrix4Elems);


    auto invoperation = InversionOperation(matrix3).execute();
    checkElems = Matrix{{-5, 2}, {3, -1}};
    assert(checkVectors(invoperation, checkElems));

    try {
        auto invoperationfail = InversionOperation(matrix4).execute();
        assert(0 == 1);
    } catch (OperationException &e) {
        assert(1 == 1);
    } catch (...) {
        assert("Wrong exception" == 0);
    }

    auto transoperation = TransposeOperation(matrix2).execute();
    checkElems = Matrix{{4, 1, 1, 4}, {5, 2, 2, 5}, {6, 3, 3, 6}};
    assert(checkVectors(transoperation, checkElems));


    auto mulnumoperation = MultiplicationNumberOperation(DMatrix, 3).execute();
    checkElems = Matrix{{21, 12, 27}, {0, 18, -9}, {12, -30, -12}};
    assert(checkVectors(mulnumoperation, checkElems));


    auto muloperation = MultiplicationOperation(matrix2, matrix).execute();
    checkElems = Matrix{{66, 81, 96}, {30, 36, 42}, {30, 36, 42}, {66, 81, 96}};
    assert(checkVectors(muloperation, checkElems));

    try {
        auto muloperationfail = MultiplicationOperation(matrix, matrix2).execute();
        assert(0 == 1);
    } catch (OperationException &e) {
        assert(1 == 1);
    } catch(...) {
        assert("Wrong exception" == 0);
    }


    auto gemoperation = GaussEliminationOperation(SMatrix).execute();
    checkElems = Matrix{{1, 0, 0, -18.25}, {0, 1, 0, 10}, {0, 0, 1, 5}, {0, 0, 0, 0}};
    assert(checkVectors(gemoperation, checkElems));


    auto trimoperation = TrimmingOperation(matrix2, 3, 3, 1, 0).execute();
    checkElems = Matrix{{1, 2, 3}, {1, 2, 3}, {4, 5, 6}};
    assert(checkVectors(trimoperation, checkElems));

    try {
        auto trimoperationfail = TrimmingOperation(matrix2, 3, 3, 1, 1).execute();
        assert(0 == 1);
    } catch (OperationException &e) {
        assert(1 == 1);
    } catch (...) {
        assert("Wrong exception" == 0);
    }

    auto joindownoperation = JoiningDownOperation(matrix2, matrix).execute();
    checkElems = Matrix{{4, 5, 6}, {1, 2, 3}, {1, 2, 3}, {4, 5, 6}, {1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    assert(checkVectors(joindownoperation, checkElems));

    try {
        auto joindownoperationfail = JoiningDownOperation(matrix, SMatrix).execute();
        assert(0 == 1);
    } catch (OperationException &e) {
        assert(1 == 1);
    } catch (...) {
        assert("Wrong exception" == 0);
    }


    auto joinrightoperation = JoiningRightOperation(DMatrix, IMatrix).execute();
    checkElems = Matrix{{7, 4, 9, 1, 0, 0}, {0, 6, -3, 0, 1, 0}, {4, -10, -4, 0, 0, 1}};
    assert(checkVectors(joinrightoperation, checkElems));


    try {
        auto joinrightoperationfail = JoiningRightOperation(matrix, SMatrix).execute();
        assert(0 == 1);
    } catch(OperationException &e) {
        assert(1 == 1);
    } catch (...) {
        assert("Wrong exception" == 0);
    }

    return 0;
}