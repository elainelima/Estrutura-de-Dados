

def print_merge_sort_tree(arr, level=0, prefix="Root: "):
    if len(arr) <= 1:
        print("  " * level + prefix + str(arr))
        return
    
    mid = len(arr) // 2
    print("  " * level + prefix + str(arr))
    
    print("  " * (level + 1) + "Left: ", end="")
    print_merge_sort_tree(arr[:mid], level + 1, "")
    
    print("  " * (level + 1) + "Right: ", end="")
    print_merge_sort_tree(arr[mid:], level + 1, "")

# Test the tree visualization
if __name__ == "__main__":
    arr = [64, 34, 25, 12, 22, 11, 90]
    print("\nMerge Sort Tree Visualization:")
    print_merge_sort_tree(arr)
