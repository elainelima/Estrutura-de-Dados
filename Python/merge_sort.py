def merge(left, right):
    """
    Função auxiliar que combina duas listas ordenadas em uma única lista ordenada.
    
    Args:
        left (list): A primeira sublista ordenada
        right (list): A segunda sublista ordenada
        
    Returns:
        list: Uma nova lista ordenada contendo todos os elementos de left e right
    """
    result = []
    i = j = 0
    
    # Compara elementos das duas listas e adiciona o menor na lista resultado
    while i < len(left) and j < len(right):
        if left[i] <= right[j]:
            result.append(left[i])
            i += 1
        else:
            result.append(right[j])
            j += 1
    
    # Adiciona os elementos restantes (se houver)
    result.extend(left[i:])
    result.extend(right[j:])
    
    return result

def mergeSort(arr):
    """
    Implementação do algoritmo Merge Sort que divide recursivamente a lista
    em sublistas menores até que tenham tamanho 1 ou 0, e depois as combina
    em ordem.
    
    Args:
        arr (list): A lista a ser ordenada
        
    Returns:
        list: Uma nova lista contendo os mesmos elementos de arr, mas ordenados
    """
    # Caso base: listas vazias ou com um único elemento já estão ordenadas
    if len(arr) <= 1:
        return arr
    
    # Divide a lista ao meio
    mid = len(arr) // 2
    left = arr[:mid]
    right = arr[mid:]
    
    # Recursivamente ordena as sublistas
    left = mergeSort(left)
    right = mergeSort(right)
    
    # Combina as sublistas ordenadas
    return merge(left, right)

# Exemplo de uso
if __name__ == "__main__":
    # Lista desordenada
    arr = [38, 27, 43, 3, 9, 82, 10]
    print("Lista original:", arr)
    
    # Aplica o Merge Sort
    sorted_arr = mergeSort(arr)
    print("Lista ordenada:", sorted_arr)
    
    # Verificando com listas diferentes
    test_cases = [
        [5, 4, 3, 2, 1],
        [1, 2, 3, 4, 5],
        [1],
        [],
        [9, 9, 8, 8, 7, 7]
    ]
    
    for i, test in enumerate(test_cases):
        print(f"\nCaso de teste {i+1}:")
        print("Entrada:", test)
        print("Saída:", mergeSort(test))

