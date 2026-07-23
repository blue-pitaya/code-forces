class Node {
  private String name;
  private Node left;
  private Node right;
  private boolean endsWithZ;

  Node(String name) {
    this.name = name;
    endsWithZ = name.endsWith("Z");
  }

  public String getName() {
    return name;
  }

  public void setLeft(Node n) {
    this.left = n;
  }

  public void setRight(Node n) {
    this.right = n;
  }

  public Node getLeft() {
    return this.left;
  }

  public Node getRight() {
    return this.right;
  }

  public boolean endsWithZ() {
    return endsWithZ;
  }
}

