class MathError(Exception):
    pass


class MatrixError(Exception):
    pass


def is_matrix(matrix: tuple | list):
    if not(type(matrix) is tuple or type(matrix) is list):
        return False
    previous_row_len = None
    for row in matrix:
        if not(type(row) is tuple or type(row) is list):
            return False
        if len(row) != previous_row_len and previous_row_len != None:
            return False
        previous_row_len = len(row)
    return True


def find_max_element(matrix):
    max = 1
    for row in matrix:
        for ele in row:
            number_of_digits = len(str(ele))
            if number_of_digits > max:
                max = number_of_digits
    return int(max)


def fill_element(element: int, number: int) -> str:
    if type(number) is not int:
        raise ValueError("Number must be an integer")
    return " " * (number - len(str(element))) + str(element)


def parse_matrix(matrix):
    result = ""
    if len(matrix) == 1:
        for element in matrix[0]:
            result += str(element) + " "
        return result.strip()
    max_digits = find_max_element(matrix)
    for row in matrix:
        for element in row:
            result += fill_element(element, max_digits) + " "
        result += "\n"
    return result.strip('\n')


def matrix_mul(a: tuple, b: tuple) -> tuple:
    if is_matrix(a) and is_matrix(b):
        if len(a[0]) != len(b):
            raise MathError("dimension ko phù hợp, ko thể nhân được")
        row = len(a)
        column = len(b[0])
        row_column_common = len(b)
        # initialize c matrix with immutable row but mutable column (need mutable to edit value later on)
        # and all init value is zero
        c = list([0] * column for _ in range(row))
        for i in range(row):
            for j in range(column):
                for x in range(row_column_common):
                    c[i][j] += a[i][x] * b[x][j]
        return c
    else:
        raise MatrixError(
            "Not a matrix."
        )


def get_matrix_from_input(matrix_name: str = "") -> list:
    name = ""
    if matrix_name != "":
        name = " " + str(matrix_name).strip()
    row = int(input(f"How many row of matrix{name}: "))
    col = int(input(f"How many column of matrix{name}: "))
    matrix = list([0] * col for _ in range(row))
    for i in range(row):
        for j in range(col):
            matrix[i][j] = int(
                input(f"Matrix element at row {i + 1} and column {j + 1} is: ")
            )
    if not is_matrix(matrix):
        raise MatrixError("This is not a matrix.")
    return matrix


def main(args):
    pass


while __name__ == "__main__":
    matrix_a = get_matrix_from_input("A")
    matrix_b = get_matrix_from_input("B")
    if len(matrix_a[0]) == len(matrix_b):
        print("\n----------------------------------------------------------")
        print("The product of matrix A:")
        print(parse_matrix(matrix_a))
        print("\nand the matrix B:")
        print(parse_matrix(matrix_b))
        print("\nis:")
        print(parse_matrix(matrix_mul(matrix_a, matrix_b)))
        print("\n----------------------------------------------------------")
    else:
        print("\n----------------------------------------------------------")
        print("Cannot multiply this two matrices.")
        print("\n----------------------------------------------------------")
