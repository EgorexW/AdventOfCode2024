def calculate_total_distance(input_file):
    """
    Calculate the total distance between two lists of numbers based on the defined process.

    Args:
        input_file (str): Path to the input file containing the two lists of numbers.

    Returns:
        int: The total distance between the two lists.
    """
    # Step 1: Read and parse the input file
    left_list = []
    right_list = []

    with open(input_file, 'r') as file:
        for line in file:
            left, right = map(int, line.split())
            left_list.append(left)
            right_list.append(right)

    # Step 2: Sort both lists in ascending order
    left_sorted = sorted(left_list)
    right_sorted = sorted(right_list)

    # Step 4: Calculate the total distance by pairing and summing absolute differences
    total_distance = sum(abs(l - r) for l, r in zip(left_sorted, right_sorted))

    return total_distance

# Example usage
input_file = "input.txt"

# Calculate and print the result
total_distance = calculate_total_distance(input_file)
print("Total Distance:", total_distance)
