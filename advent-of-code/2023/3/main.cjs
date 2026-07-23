const fs = require("fs");
const filePath = "input.txt";

fs.readFile(filePath, "utf8", (_, data) => {
  const lines = data.split("\n");

  const nums = [];
  const validNums = new Set();

  //part 1
  lines.forEach((line, y) => {
    Array.from(line.matchAll(/\d+/g)).forEach((match) => {
      const x = match.index;
      const v = match[0];
      const len = v.length;
      const x2 = x + len;

      nums.push({ x, y, x2, v });
    });
  });

  lines.forEach((line, y) => {
    Array.from(line.matchAll(/[^0-9.]/g)).forEach((match) => {
      const x = match.index;

      for (let i = x - 1; i <= x + 1; i++) {
        for (let j = y - 1; j <= y + 1; j++) {
          nums.forEach((num) => {
            if (num.y === j && num.x <= i && i < num.x2) {
              validNums.add(num);
            }
          });
        }
      }
    });
  });

  console.log(Array.from(validNums).reduce((acc, n) => acc + Number(n.v), 0));

  //part 2
  let sum = 0;

  lines.forEach((line, y) => {
    Array.from(line.matchAll(/\*/g)).forEach((match) => {
      const x = match.index;
      const adjNums = new Set();

      for (let i = x - 1; i <= x + 1; i++) {
        for (let j = y - 1; j <= y + 1; j++) {
          nums.forEach((num) => {
            if (num.y === j && num.x <= i && i < num.x2) {
              adjNums.add(num);
            }
          });
        }
      }

      if (adjNums.size == 2) {
        const ns = Array.from(adjNums);
        sum += Number(ns[0].v) * Number(ns[1].v);
      }
    });
  });

  console.log(sum);
});
