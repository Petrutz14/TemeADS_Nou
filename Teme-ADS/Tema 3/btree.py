class Node:
    def __init__(self, leaf=False):
        self.leaf = leaf
        self.keys = []
        self.child = []

class BTree:
    def __init__(self, t):
        self.root = Node(True)
        self.t = t  #Grad maxim

    def split_child(self, parent, i):
        t = self.t
        node_to_split = parent.child[i]
        new_node = Node(node_to_split.leaf)
        
        #Parintele primeste cheia din mijloc
        parent.keys.insert(i, node_to_split.keys[t - 1])
        
        #Split chei: noul nod ia jumatatea de sus
        new_node.keys = node_to_split.keys[t : (2 * t) - 1]
        node_to_split.keys = node_to_split.keys[0 : t - 1]

        #Daca nu e frunza, mutam si copiii
        if not node_to_split.leaf:
            new_node.child = node_to_split.child[t : 2 * t]
            node_to_split.child = node_to_split.child[0 : t]

        parent.child.insert(i + 1, new_node)

    def insert_non_full(self, x, k):
        i = len(x.keys) - 1
        
        if x.leaf:
            #Inserare in frunza in ordine crescatoare
            x.keys.append(None)
            while i >= 0 and k < x.keys[i]:
                x.keys[i + 1] = x.keys[i]
                i -= 1
            x.keys[i + 1] = k
        else:
            #Gasim copilul potrivit pentru coborare
            while i >= 0 and k < x.keys[i]:
                i -= 1
            i += 1
            #Daca copilul e plin, il splituim inainte sa intram
            if len(x.child[i].keys) == (2 * self.t) - 1:
                self.split_child(x, i)
                if k > x.keys[i]:
                    i += 1
            self.insert_non_full(x.child[i], k)

    def insert(self, k):
        root = self.root
        #Daca root e plin, copacul creste in inaltime
        if len(root.keys) == (2 * self.t) - 1:
            temp = Node()
            self.root = temp
            temp.child.insert(0, root)
            self.split_child(temp, 0)
            self.insert_non_full(temp, k)
        else:
            self.insert_non_full(root, k)

    def search(self, k, node=None):
        if node is None: node = self.root
        
        i = 0
        while i < len(node.keys) and k > node.keys[i]:
            i += 1
        
        if i < len(node.keys) and k == node.keys[i]:
            return True
        
        if node.leaf:
            return False
            
        return self.search(k, node.child[i])

if __name__ == "__main__":
    tree = BTree(3)

    #Inserari
    tree.insert(10)
    tree.insert(20)
    tree.insert(5)
    tree.insert(6)
    tree.insert(12)
    tree.insert(30)
    tree.insert(7)
    tree.insert(17)

    #Cautari
    print(f"E 12 in copac? {'DA' if tree.search(12) else 'NU'}")
    print(f"E 30 in copac? {'DA' if tree.search(30) else 'NU'}")
    print(f"E 100 in copac? {'DA' if tree.search(100) else 'NU'}")

    #Structura radacinii
    print("Chei in radacina:", tree.root.keys)