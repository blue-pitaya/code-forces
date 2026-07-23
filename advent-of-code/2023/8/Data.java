import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.HashMap;
import java.util.stream.LongStream;

class Data {
  private String directions;
  private HashMap<String, Node> lookup;

  Data(String filePath) throws IOException {
    lookup = new HashMap<>();

    try (BufferedReader reader = new BufferedReader(new FileReader(filePath))) {
      String line;
      int lineNum = 0;

      while ((line = reader.readLine()) != null) {
        if (lineNum == 0) {
          directions = line;
        }
        if (lineNum > 1) {
          String[] parts = line.split(" ");
          String name = parts[0];
          String leftName = parts[2].substring(1, parts[2].length() - 1);
          String rightName = parts[3].substring(0, parts[3].length() - 1);

          Node left = lookup.get(leftName);
          if (left == null) {
            left = new Node(leftName);
            lookup.put(leftName, left);
          }
          Node right = lookup.get(rightName);
          if (right == null) {
            right = new Node(rightName);
            lookup.put(rightName, right);
          }

          Node n = lookup.get(name);
          if (n == null) {
            n = new Node(name);
            lookup.put(name, n);
          }

          n.setLeft(left);
          n.setRight(right);
        }

        lineNum++;
      }
    } catch (IOException e) {
      throw e;
    }
  }

  public void solve1() throws Exception {
    int steps = 0;
    Node n = lookup.get("AAA");

    while (!n.getName().equals("ZZZ")) {
      char c = directions.charAt(steps % directions.length());

      switch (c) {
        case 'L':
          n = n.getLeft();
          break;
        case 'R':
          n = n.getRight();
          break;
        default:
          throw new Exception();
      }

      steps++;
    }

    System.out.println(steps);
  }

  private boolean isEveryNodeAtZ(Node[] nodes) {
    for (Node n : nodes) {
      if (!n.endsWithZ()) {
        return false;
      }
    }

    return true;
  }

  public void solve22() throws Exception {
    int steps = 0;

    Node[] nodes = lookup.values().stream().filter(n -> n.getName().endsWith("A")).toArray(Node[]::new);
    int[] firstEnd = new int[nodes.length];
    int[] secondEnd = new int[nodes.length];
    int seconds = 0;

    while (!isEveryNodeAtZ(nodes)) {
      char c = directions.charAt(steps % directions.length());
      steps++;

      for (int i = 0; i < nodes.length; i++) {
        Node n = nodes[i];

        switch (c) {
          case 'L':
            n = n.getLeft();
            break;
          case 'R':
            n = n.getRight();
            break;
          default:
            throw new Exception();
        }
        if (n.endsWithZ()) {
          if (firstEnd[i] != 0) {
            secondEnd[i] = steps;
            seconds++;
          } else {
            firstEnd[i] = steps;
          }
        }

        nodes[i] = n;
      }

      if (seconds > nodes.length) {
        break;
      }
    }

    long[] diffs = new long[secondEnd.length];
    for (int i = 0; i < secondEnd.length; i++) {
      // this is sheer luck that every start -> end steps are the same as end -> end steps
      // if cycle end -> end was different then i would be fucked xd
      diffs[i] = firstEnd[i];
    }

    System.out.println(calculateLCM(diffs));

  }

  private static long calculateLCM(long[] numbers) {
    long lcm = LongStream.of(numbers)
        .reduce((a, b) -> a * b / gcd(a, b))
        .orElse(1);

    return lcm;
  }

  private static long gcd(long a, long b) {
    while (b > 0) {
      long temp = b;
      b = a % b;
      a = temp;
    }
    return a;
  }
}
