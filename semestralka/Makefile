CXX = g++
CXXFLAGS = -Wall -pedantic -std=c++17

TARGET = gordeser
BUILD_DIR = build
EXPORT_DIR = export

HEADERS = $(wildcard src/*.h src/*/*.h) # finding files using template
SOURCES = $(wildcard src/*.cpp src/*/*.cpp)
OBJECTS = $(SOURCES:src/%.cpp=$(BUILD_DIR)/%.o) # change .cpp files to build/%.o file

.PHONY: all
all: compile doc

.PHONY: run
run: compile
	./$(TARGET)

.PHONY: compile
compile: $(TARGET)
	mkdir -p $(EXPORT_DIR)
	cp examples/example.out $(EXPORT_DIR)

$(TARGET): $(BUILD_DIR)/main
	# copy file BUILD_DIR/main into TARGET
	cp $< $@

$(BUILD_DIR)/main: $(OBJECTS)
	# create folder BUILD_DIR if does not exists
	mkdir -p $(@D)
	# compile all OBJECTS files into file BUILD_DIR/main
	$(CXX) $^ -o $@

$(BUILD_DIR)/%.o: src/%.cpp
	# create folder BUILD_DIR/% if does not exists
	mkdir -p $(@D)
	# create object file %.cpp with given flags, output it in BUILD_DIR/%.o
	$(CXX) $(CXXFLAGS) $< -c -o $@

doc: Doxyfile $(HEADERS)
	doxygen Doxyfile

.PHONY: clean
clean:
	rm -rf $(TARGET) $(BUILD_DIR)/ doc/ export/ 2>/dev/null



# Dependencies
ExecuterException.o: src/Exceptions/ExecuterException.cpp \
 src/Exceptions/ExecuterException.h
ExporterException.o: src/Exceptions/ExporterException.cpp \
 src/Exceptions/ExporterException.h
MatrixException.o: src/Exceptions/MatrixException.cpp \
 src/Exceptions/MatrixException.h
OperationException.o: src/Exceptions/OperationException.cpp \
 src/Exceptions/OperationException.h
ParserException.o: src/Exceptions/ParserException.cpp \
 src/Exceptions/ParserException.h
StorageException.o: src/Exceptions/StorageException.cpp \
 src/Exceptions/StorageException.h
TextExport.o: src/Exports/TextExport.cpp src/Exports/TextExport.h \
 src/Exports/Export.h src/Exports/../Matrices/Matrix.h \
 src/Exports/../MatrixStorage.h src/Exports/../Matrices/Matrix.h \
 src/Exports/../Utilities.h src/Exports/../Matrices/DenseMatrix.h \
 src/Exports/../Matrices/Matrix.h src/Exports/../Matrices/SparseMatrix.h \
 src/Exports/../Matrices/IdentityMatrix.h \
 src/Exports/../Exceptions/ExporterException.h
DenseMatrix.o: src/Matrices/DenseMatrix.cpp src/Matrices/DenseMatrix.h \
 src/Matrices/Matrix.h src/Matrices/../Exceptions/MatrixException.h
IdentityMatrix.o: src/Matrices/IdentityMatrix.cpp \
 src/Matrices/IdentityMatrix.h src/Matrices/Matrix.h
Matrix.o: src/Matrices/Matrix.cpp \
 src/Matrices/../Exceptions/MatrixException.h \
 src/Matrices/../Operations/GaussEliminationOperation.h \
 src/Matrices/../Operations/Operation.h \
 src/Matrices/../Operations/../Matrices/Matrix.h \
 src/Matrices/../Operations/../Utilities.h \
 src/Matrices/../Operations/../Matrices/DenseMatrix.h \
 src/Matrices/../Operations/../Matrices/Matrix.h \
 src/Matrices/../Operations/../Matrices/SparseMatrix.h \
 src/Matrices/../Operations/../Matrices/IdentityMatrix.h \
 src/Matrices/Matrix.h
SparseMatrix.o: src/Matrices/SparseMatrix.cpp src/Matrices/SparseMatrix.h \
 src/Matrices/Matrix.h src/Matrices/../Exceptions/MatrixException.h
AdditionOperation.o: src/Operations/AdditionOperation.cpp \
 src/Operations/AdditionOperation.h src/Operations/BinaryOperation.h \
 src/Operations/Operation.h src/Operations/../Matrices/Matrix.h \
 src/Operations/../Exceptions/OperationException.h
BinaryOperation.o: src/Operations/BinaryOperation.cpp \
 src/Operations/BinaryOperation.h src/Operations/Operation.h \
 src/Operations/../Matrices/Matrix.h
ExponentiationOperation.o: src/Operations/ExponentiationOperation.cpp \
 src/Operations/ExponentiationOperation.h \
 src/Operations/BinaryOperation.h src/Operations/Operation.h \
 src/Operations/../Matrices/Matrix.h src/Operations/../Utilities.h \
 src/Operations/../Matrices/DenseMatrix.h \
 src/Operations/../Matrices/Matrix.h \
 src/Operations/../Matrices/SparseMatrix.h \
 src/Operations/../Matrices/IdentityMatrix.h \
 src/Operations/MultiplicationOperation.h \
 src/Operations/../Exceptions/OperationException.h
GaussEliminationOperation.o: src/Operations/GaussEliminationOperation.cpp \
 src/Operations/GaussEliminationOperation.h src/Operations/Operation.h \
 src/Operations/../Matrices/Matrix.h src/Operations/../Utilities.h \
 src/Operations/../Matrices/DenseMatrix.h \
 src/Operations/../Matrices/Matrix.h \
 src/Operations/../Matrices/SparseMatrix.h \
 src/Operations/../Matrices/IdentityMatrix.h
InversionOperation.o: src/Operations/InversionOperation.cpp \
 src/Operations/InversionOperation.h src/Operations/Operation.h \
 src/Operations/../Matrices/Matrix.h src/Operations/../Utilities.h \
 src/Operations/../Matrices/DenseMatrix.h \
 src/Operations/../Matrices/Matrix.h \
 src/Operations/../Matrices/SparseMatrix.h \
 src/Operations/../Matrices/IdentityMatrix.h \
 src/Operations/../Exceptions/OperationException.h \
 src/Operations/JoiningRightOperation.h src/Operations/BinaryOperation.h \
 src/Operations/TrimmingOperation.h
JoiningDownOperation.o: src/Operations/JoiningDownOperation.cpp \
 src/Operations/JoiningDownOperation.h src/Operations/BinaryOperation.h \
 src/Operations/Operation.h src/Operations/../Matrices/Matrix.h \
 src/Operations/../Exceptions/OperationException.h
JoiningRightOperation.o: src/Operations/JoiningRightOperation.cpp \
 src/Operations/JoiningRightOperation.h src/Operations/BinaryOperation.h \
 src/Operations/Operation.h src/Operations/../Matrices/Matrix.h \
 src/Operations/../Exceptions/OperationException.h
MultiplicationNumberOperation.o: \
 src/Operations/MultiplicationNumberOperation.cpp \
 src/Operations/MultiplicationNumberOperation.h \
 src/Operations/Operation.h src/Operations/../Matrices/Matrix.h
MultiplicationOperation.o: src/Operations/MultiplicationOperation.cpp \
 src/Operations/MultiplicationOperation.h \
 src/Operations/BinaryOperation.h src/Operations/Operation.h \
 src/Operations/../Matrices/Matrix.h \
 src/Operations/../Exceptions/OperationException.h
Operation.o: src/Operations/Operation.cpp src/Operations/Operation.h \
 src/Operations/../Matrices/Matrix.h
SubtractionOperation.o: src/Operations/SubtractionOperation.cpp \
 src/Operations/SubtractionOperation.h src/Operations/BinaryOperation.h \
 src/Operations/Operation.h src/Operations/../Matrices/Matrix.h \
 src/Operations/../Exceptions/OperationException.h
TransposeOperation.o: src/Operations/TransposeOperation.cpp \
 src/Operations/TransposeOperation.h src/Operations/Operation.h \
 src/Operations/../Matrices/Matrix.h
TrimmingOperation.o: src/Operations/TrimmingOperation.cpp \
 src/Operations/TrimmingOperation.h src/Operations/Operation.h \
 src/Operations/../Matrices/Matrix.h \
 src/Operations/../Exceptions/OperationException.h
ConsoleUI.o: src/UserInterfaces/ConsoleUI.cpp \
 src/UserInterfaces/ConsoleUI.h src/UserInterfaces/UserInterface.h
Executer.o: src/Executer.cpp src/Executer.h src/Matrices/Matrix.h \
 src/Utilities.h src/Matrices/DenseMatrix.h src/Matrices/Matrix.h \
 src/Matrices/SparseMatrix.h src/Matrices/IdentityMatrix.h \
 src/MatrixStorage.h src/Operations/Operation.h \
 src/Operations/../Matrices/Matrix.h src/Commands.h \
 src/Operations/ExponentiationOperation.h \
 src/Operations/BinaryOperation.h src/Operations/Operation.h \
 src/Operations/../Utilities.h src/Exceptions/ExecuterException.h \
 src/Operations/TransposeOperation.h src/Operations/InversionOperation.h \
 src/Operations/GaussEliminationOperation.h \
 src/Operations/AdditionOperation.h src/Operations/SubtractionOperation.h \
 src/Operations/MultiplicationNumberOperation.h \
 src/Operations/MultiplicationOperation.h \
 src/Operations/JoiningRightOperation.h \
 src/Operations/JoiningDownOperation.h src/Operations/TrimmingOperation.h
MatrixCalculator.o: src/MatrixCalculator.cpp src/MatrixCalculator.h \
 src/Parser.h src/MatrixStorage.h src/Matrices/Matrix.h \
 src/UserInterfaces/ConsoleUI.h src/UserInterfaces/UserInterface.h \
 src/Utilities.h src/Matrices/DenseMatrix.h src/Matrices/Matrix.h \
 src/Matrices/SparseMatrix.h src/Matrices/IdentityMatrix.h src/Executer.h \
 src/Exports/TextExport.h src/Exports/Export.h \
 src/Exports/../Matrices/Matrix.h src/Exports/../MatrixStorage.h \
 src/Exports/../Utilities.h src/Exceptions/ExporterException.h \
 src/Exceptions/MatrixException.h src/Exceptions/OperationException.h \
 src/Exceptions/ParserException.h src/Exceptions/StorageException.h \
 src/Exceptions/ExecuterException.h
MatrixStorage.o: src/MatrixStorage.cpp src/MatrixStorage.h \
 src/Matrices/Matrix.h src/Exceptions/StorageException.h
Parser.o: src/Parser.cpp src/Parser.h src/MatrixStorage.h \
 src/Matrices/Matrix.h src/UserInterfaces/ConsoleUI.h \
 src/UserInterfaces/UserInterface.h src/Utilities.h \
 src/Matrices/DenseMatrix.h src/Matrices/Matrix.h \
 src/Matrices/SparseMatrix.h src/Matrices/IdentityMatrix.h src/Executer.h \
 src/Exports/TextExport.h src/Exports/Export.h \
 src/Exports/../Matrices/Matrix.h src/Exports/../MatrixStorage.h \
 src/Exports/../Utilities.h src/Commands.h \
 src/Exceptions/ParserException.h
Utilities.o: src/Utilities.cpp src/Utilities.h src/Matrices/DenseMatrix.h \
 src/Matrices/Matrix.h src/Matrices/SparseMatrix.h \
 src/Matrices/IdentityMatrix.h src/Commands.h
main.o: src/main.cpp src/MatrixCalculator.h src/Parser.h \
 src/MatrixStorage.h src/Matrices/Matrix.h src/UserInterfaces/ConsoleUI.h \
 src/UserInterfaces/UserInterface.h src/Utilities.h \
 src/Matrices/DenseMatrix.h src/Matrices/Matrix.h \
 src/Matrices/SparseMatrix.h src/Matrices/IdentityMatrix.h src/Executer.h \
 src/Exports/TextExport.h src/Exports/Export.h \
 src/Exports/../Matrices/Matrix.h src/Exports/../MatrixStorage.h \
 src/Exports/../Utilities.h