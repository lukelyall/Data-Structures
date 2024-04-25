class Node:
  def __init__(self, data, next=None):
    self.data = data
    self.next = next

class LinkedList:
  def __init__(self):
    self.head = None
    self.tail = None

  def createNode(self, data):
    temp = Node(data)

    if self.head is None:
      self.head = temp
      self.tail = temp
    else:
      self.tail.next = temp
      self.tail = temp

  def printLinkedList(self):
    current = self.head
    while current is not None:
      print(current.data)
      current = current.next

if __name__ == '__main__':
  linkedlist = LinkedList()

  linkedlist.createNode(15)
  linkedlist.createNode(19)
  linkedlist.createNode(22)

  linkedlist.printLinkedList()