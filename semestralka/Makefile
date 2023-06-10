CXX = g++
CXXFLAGS = -Wall -pedantic -std=c++17

TARGET = gordeser
BUILD_DIR = build
EXPORT_DIR = export

HEADERS = $(wildcard src/*.h src/*/*.h) # finding files using template
SOURCES = $(wildcard src/*.cpp src/*/*.cpp)
OBJECTS = $(SOURCES:src/%.cpp=$(BUILD_DIR)/%.o) # change .cpp files to build/%.o file

.PHONY: all
all: compile

.PHONY: run
run: compile
	# will be run after successful compile
	./$(TARGET)

.PHONY: compile
compile: $(TARGET)
	mkdir -p $(EXPORT_DIR)

$(TARGET): $(BUILD_DIR)/main
	cp $< $@  # copy file BUILD_DIR/main into TARGET

$(BUILD_DIR)/main: $(OBJECTS)
	mkdir -p $(@D)  # create folder BUILD_DIR if does not exists
	$(CXX) $^ -o $@  # compile all OBJECTS files into file BUILD_DIR/main

$(BUILD_DIR)/%.o: src/%.cpp
	mkdir -p $(@D) # create folder BUILD_DIR/% if does not exists
	$(CXX) $(CXXFLAGS) $< -c -o $@ # create object file %.cpp with given flags, output it in BUILD_DIR/%.o

doc: Doxyfile $(HEADERS)
	doxygen Doxyfile # run command doxygen Doxyfile

.PHONY: clean
clean:
	rm -rf $(TARGET) $(BUILD_DIR)/ doc/ export/ 2>/dev/null



# Dependencies
Utilities.o: Utilities.cpp Utilities.h Matrices/DenseMatrix.h \
 Matrices/Matrix.h Matrices/SparseMatrix.h Matrices/IdentityMatrix.h \
 Commands.h
Parser.o: Parser.cpp Parser.h MatrixStorage.h Matrices/Matrix.h \
 UserInterfaces/ConsoleUI.h UserInterfaces/UserInterface.h Utilities.h \
 Matrices/DenseMatrix.h Matrices/Matrix.h Matrices/SparseMatrix.h \
 Matrices/IdentityMatrix.h Exports/TextExport.h Exports/Export.h \
 Exports/../Matrices/Matrix.h Exports/../MatrixStorage.h \
 Exports/../Utilities.h Commands.h Operations/AdditionOperation.h \
 Operations/BinaryOperation.h Operations/Operation.h \
 Exceptions/ParserException.h
MatrixStorage.o: MatrixStorage.cpp MatrixStorage.h Matrices/Matrix.h \
 Exceptions/StorageException.h
MatrixCalculator.o: MatrixCalculator.cpp MatrixCalculator.h Parser.h \
 MatrixStorage.h Matrices/Matrix.h UserInterfaces/ConsoleUI.h \
 UserInterfaces/UserInterface.h Utilities.h Matrices/DenseMatrix.h \
 Matrices/Matrix.h Matrices/SparseMatrix.h Matrices/IdentityMatrix.h \
 Exports/TextExport.h Exports/Export.h Exports/../Matrices/Matrix.h \
 Exports/../MatrixStorage.h Exports/../Utilities.h \
 Exceptions/ExporterException.h Exceptions/MatrixException.h \
 Exceptions/OperationException.h Exceptions/ParserException.h \
 Exceptions/StorageException.h
main.o: main.cpp MatrixCalculator.h Parser.h MatrixStorage.h \
 Matrices/Matrix.h UserInterfaces/ConsoleUI.h \
 UserInterfaces/UserInterface.h Utilities.h Matrices/DenseMatrix.h \
 Matrices/Matrix.h Matrices/SparseMatrix.h Matrices/IdentityMatrix.h \
 Exports/TextExport.h Exports/Export.h Exports/../Matrices/Matrix.h \
 Exports/../MatrixStorage.h Exports/../Utilities.h
ConsoleUI.o: UserInterfaces/ConsoleUI.cpp UserInterfaces/ConsoleUI.h \
 UserInterfaces/UserInterface.h
AdditionOperation.o: Operations/AdditionOperation.cpp \
 Operations/AdditionOperation.h Operations/BinaryOperation.h \
 Operations/Operation.h Operations/../Matrices/Matrix.h \
 Operations/../Exceptions/OperationException.h
BinaryOperation.o: Operations/BinaryOperation.cpp \
 Operations/BinaryOperation.h Operations/Operation.h \
 Operations/../Matrices/Matrix.h
ExponentiationOperation.o: Operations/ExponentiationOperation.cpp \
 Operations/ExponentiationOperation.h Operations/BinaryOperation.h \
 Operations/Operation.h Operations/../Matrices/Matrix.h \
 Operations/../Utilities.h Operations/../Matrices/DenseMatrix.h \
 Operations/../Matrices/Matrix.h Operations/../Matrices/SparseMatrix.h \
 Operations/../Matrices/IdentityMatrix.h \
 Operations/MultiplicationOperation.h \
 Operations/../Exceptions/OperationException.h
GaussEliminationOperation.o: Operations/GaussEliminationOperation.cpp \
 Operations/GaussEliminationOperation.h Operations/Operation.h \
 Operations/../Matrices/Matrix.h
InversionOperation.o: Operations/InversionOperation.cpp \
 Operations/InversionOperation.h Operations/Operation.h \
 Operations/../Matrices/Matrix.h Operations/../Utilities.h \
 Operations/../Matrices/DenseMatrix.h Operations/../Matrices/Matrix.h \
 Operations/../Matrices/SparseMatrix.h \
 Operations/../Matrices/IdentityMatrix.h \
 Operations/../Exceptions/OperationException.h \
 Operations/JoiningRightOperation.h Operations/BinaryOperation.h \
 Operations/TrimmingOperation.h
JoiningDownOperation.o: Operations/JoiningDownOperation.cpp \
 Operations/JoiningDownOperation.h Operations/BinaryOperation.h \
 Operations/Operation.h Operations/../Matrices/Matrix.h \
 Operations/../Exceptions/OperationException.h
JoiningRightOperation.o: Operations/JoiningRightOperation.cpp \
 Operations/JoiningRightOperation.h Operations/BinaryOperation.h \
 Operations/Operation.h Operations/../Matrices/Matrix.h \
 Operations/../Exceptions/OperationException.h
MultiplicationNumberOperation.o: \
 Operations/MultiplicationNumberOperation.cpp \
 Operations/MultiplicationNumberOperation.h Operations/Operation.h \
 Operations/../Matrices/Matrix.h
MultiplicationOperation.o: Operations/MultiplicationOperation.cpp \
 Operations/MultiplicationOperation.h Operations/BinaryOperation.h \
 Operations/Operation.h Operations/../Matrices/Matrix.h \
 Operations/../Exceptions/OperationException.h
Operation.o: Operations/Operation.cpp Operations/Operation.h \
 Operations/../Matrices/Matrix.h
SubtractionOperation.o: Operations/SubtractionOperation.cpp \
 Operations/SubtractionOperation.h Operations/BinaryOperation.h \
 Operations/Operation.h Operations/../Matrices/Matrix.h \
 Operations/../Exceptions/OperationException.h
TransposeOperation.o: Operations/TransposeOperation.cpp \
 Operations/TransposeOperation.h Operations/Operation.h \
 Operations/../Matrices/Matrix.h
TrimmingOperation.o: Operations/TrimmingOperation.cpp \
 Operations/TrimmingOperation.h Operations/Operation.h \
 Operations/../Matrices/Matrix.h \
 Operations/../Exceptions/OperationException.h
DenseMatrix.o: Matrices/DenseMatrix.cpp Matrices/DenseMatrix.h \
 Matrices/Matrix.h
IdentityMatrix.o: Matrices/IdentityMatrix.cpp Matrices/IdentityMatrix.h \
 Matrices/Matrix.h
Matrix.o: Matrices/Matrix.cpp Matrices/../Exceptions/MatrixException.h \
 Matrices/../Operations/GaussEliminationOperation.h \
 Matrices/../Operations/Operation.h \
 Matrices/../Operations/../Matrices/Matrix.h Matrices/Matrix.h
SparseMatrix.o: Matrices/SparseMatrix.cpp Matrices/SparseMatrix.h \
 Matrices/Matrix.h
TextExport.o: Exports/TextExport.cpp Exports/TextExport.h \
 Exports/Export.h Exports/../Matrices/Matrix.h Exports/../MatrixStorage.h \
 Exports/../Matrices/Matrix.h Exports/../Utilities.h \
 Exports/../Matrices/DenseMatrix.h Exports/../Matrices/Matrix.h \
 Exports/../Matrices/SparseMatrix.h Exports/../Matrices/IdentityMatrix.h \
 Exports/../Exceptions/ExporterException.h
ExporterException.o: Exceptions/ExporterException.cpp \
 Exceptions/ExporterException.h
MatrixException.o: Exceptions/MatrixException.cpp \
 Exceptions/MatrixException.h
OperationException.o: Exceptions/OperationException.cpp \
 Exceptions/OperationException.h
ParserException.o: Exceptions/ParserException.cpp \
 Exceptions/ParserException.h
StorageException.o: Exceptions/StorageException.cpp \
 Exceptions/StorageException.h
