# Matrix Calculator

## Goals

The main goal of the application is to practice working with OOP concepts such as polymorphism, inheritance, and encapsulation. Besides, the project aims to develop practical skills in C++ by working with it's features like Standard Template Library (STL), classes and smart pointers

## Matrix Operations

The matrix calculator includes **binary** operations:
- Matrix addition `X = ADD A B`
- Matrix subtraction `X = SUB A B`
- Scalar multiplication `X = MUL a A`
- Matrix multiplication `X = MUL A B`
- Matrix merging from the right `X = JOINRIGHT A B`
- Matrix merging from the below `X = JOINDOWN A B`
- Matrix trimming `X = TRIM A row col off_x off_y`
- Matrix exponentiation `X = EXP A a`


And **unary** operations:
- Matrix transposition `X = TRANS A`
- Calculation of the inverse matrix (square matrices only) `X = INV A`
- Determinant calculation (square matrices only) `X = DET A`
- Rank determination `X = RANK A`
- Gaussian elimination `X = GEM A`

## Types of matrices

For efficiency, the calculator differentiates between three types of matrices:
- Sparse matrix: 
    - matrix with a majority of zero elements (>50% zeros)
    - stored using **map** (more efficient data type)
- Dense matrix:
    - matrix with a majority of nonzero elements (>50% nonzeros)
    - stored as a 2D array
- Identity matrix
    - matrix with ones on the main diagonal

## Input/Output Matrix Operations

Additionally, the user can manage matrix data:
- Input a matrix `SCAN X`
- Import matrices from a file `IMPORT filename`
- Delete a matrix `DEL X`
- Delete all matrices `DELALL`
- Export matrices to a file `EXPORT filename X`
- Export all matrices to a file `EXPORTALL filename`
- Display matrices in the console `PRINT X`
- Display all matrices in the console `PRINTALL`


## File Handling Specifications

- If the specified output file does not exist, it will be created.
- If the specified output file contains data, it will be erased.
- The file will be saved in the `export` directory, which is in the same directory as the program.
- To import a matrix, the file must be located in the `export` directory, which is in the same directory as the program.
- To import a matrix, the file must be properly formatted as shown in the examples.
- If an invalid or incorrectly formatted file is provided, the program will display an error message.


## Console Interaction

- The calculator operates via the command-line interface (CLI).
- The user enters a command or multiple commands in a single line (e.g., `A = GEM MUL Y ADD Z X`).
- If an error occurs, the program terminates execution of a command and displays an error message with a brief description.
- The user can exit the program using the `EXIT` or `QUIT` command.
- The user can use the `HELP` command to display all available commands.


## Polymorphism

### Matrices

Polymorphism is primarily used in the abstract class `Matrix`, from which the classes `SparseMatrix`, `DenseMatrix`, and `IdentityMatrix` inherit.

The `Matrix` class uses virtual methods:
- `getVal` – retrieves a matrix value
- `rank` – computes the rank of a matrix
- `determinant` – calculates the determinant of a matrix
- `clone` – performs a deep copy of a matrix
- `print` – displays the matrix
- `printToFile` – outputs the matrix in a file-compatible format


### Matrix Operations

Polymorphism is also applied in the abstract class `Operation`, from which `BinaryOperation` and all unary operations (e.g., `Transpose`, `Inverse`, etc.) inherit.

All binary operations (`Addition`, `Subtraction`, etc.) inherit from `BinaryOperation`.
The `Operation` class uses the virtual method execute to perform operations.

### File Handling

Additionally, polymorphism is used in the abstract class `Export`, which is responsible for export/import formats (text, binary, etc.).
For now, export is implemented only as a text file via the `TextExport` subclass, but future expansion is possible.

The `Export` class uses virtual methods:
- `exportData` – outputs data in the required format
- `importData` – loads data from a file

### User Interfaces

Finally, polymorphism is applied in the abstract class `UserInterface`, which supports different user interfaces.
Currently, the user interface is implemented only as a console interface via the `ConsoleUI` subclass, but future expansion is also possible

The `UserInterface` class uses virtual methods:
- `showText` – displays text on the screen
- `getInput` – receives user input

