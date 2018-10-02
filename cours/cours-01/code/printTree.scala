object Example1 {

class Tree
case class Leaf (x: Int) extends Tree
case class Node (x: Int, children : List[Tree]) extends Tree

def mkIndent (size : Int) : String =
  if (size == 0) "" else " " + mkIndent (size - 1)

type Document = {
  def printItem (s: String) : Unit
  def startEnumeration : Unit
  def stopEnumeration  : Unit
}

object ConsoleDocument {
  var offset = 0
  def printItem (s: String) = println (mkIndent (offset) + s)
  def startEnumeration = offset += 2
  def stopEnumeration  = offset -= 2
}

object HTMLDocument {
  def printItem (s: String) = println ("<li>" + s + "</li>")
  def startEnumeration      = println ("<ul>")
  def stopEnumeration       = println ("</ul>")
}

def printTree (tree : Tree, doc : Document) : Unit =
  tree match {
    case Leaf (x) => doc.printItem (x.toString)
    case Node (x, children) => {
      doc.printItem (x.toString)
      doc.startEnumeration;
      children.foreach (child => printTree (child, doc));
      doc.stopEnumeration;
    }
  }

def t = Node (1, List(Leaf (2), Node (3, List(Leaf (4), Leaf (5)))))
printTree (t, ConsoleDocument)
printTree (t, HTMLDocument)

}
