# Definition for a binary tree node.
class TreeNode(object):
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right
def insert(root,val):
    root = TreeNode(val)
    print("Inclass",root.val)
a = TreeNode(1)
insert(a.left,2)
print(a.left.val)
