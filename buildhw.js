#!/usr/bin/env zx
import fs from "fs";

const INCLUDES = ["./stdhw"];
const HW_DIR = "hws";
const CC = "clang";
const CARGS = [
  "-Wall",
  "-Wextra",
  "-Wpedantic",
  ...INCLUDES.map((e) => `-I${e}`),
];

if (argv._.length !== 1) {
  console.log("Укажите название ДЗ");
  process.exit(1);
}

await $`mkdir -p build`;

const sources = [
  ...(await glob("./stdhw/*.c")),
  ...(await glob(`./${HW_DIR}/${argv._[0]}/*.c`)),
];

const sourceHashes = new Map();
const hashProms = [];

for (const source of sources) {
  hashProms.push(
    $`md5 -q ${source}`.then((e) => {
      sourceHashes.set(source, e.stdout.trim());
    }),
  );
}

await Promise.all(hashProms);

const compilationPromises = [];
const objectFiles = [];

for (const [name, hash] of sourceHashes.entries()) {
  objectFiles.push(`./build/${hash}.o`);
  if (fs.existsSync(`./build/${hash}.o`)) {
    console.log(`Переиспользуем объектный файл ${name}(hash = ${hash})`);
    continue;
  }

  compilationPromises.push($`${CC} ${CARGS} ${name} -c -o ./build/${hash}.o`);
  console.log(`Компилируем ${name}(hash = ${hash})`);
}

await Promise.all(compilationPromises);

await $`gcc ${objectFiles} -o ./build/${argv._[0]}`;
console.log(`Вывод в файле ./build/${argv._[0]}`);
