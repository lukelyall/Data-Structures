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

  def deleteLastNode(self):
    if self.head == None:
      print("empty linked list\n")
      return
    
    if self.head == self.tail:
      self.head = None
      self.tail = None
      return

    previous = self.head

    while(previous.next != self.tail):
      previous = previous.next
    
    previous.next = None
    self.tail = previous

  def deleteFirstData(self, data):
    current = self.head
    previous = self.head

    while current != None:
      if current.data == data:
        if previous == None:
          self.head = current.next
        else:
          previous.next = current.next
        current = None
        return
      previous = current
      current = current.next

  def searchLinkedList(self, data):
    current = self.head

    while current != None:
      if current.data == data:
        print("found:", data)
        return
      current = current.next

  def printLinkedList(self):
    print("linked list:")
    current = self.head
    while current is not None:
      print(current.data)
      current = current.next

if __name__ == '__main__':
  linkedlist = LinkedList()

  linkedlist.createNode(15)
  linkedlist.createNode(19)
  linkedlist.createNode(5)
  linkedlist.createNode(10)
  linkedlist.createNode(22)

  linkedlist.searchLinkedList(22)

  linkedlist.deleteLastNode()
  linkedlist.deleteFirstData(19)

  linkedlist.printLinkedList()