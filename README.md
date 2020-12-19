Filesystem interface library of the Chaos language. You can install this spell with:

```bash
occultist install fs
```

and import it with:

```chaos
import fs
```

## I/O

### num fs.open(str filepath, str mode)

Open a file on path `filepath` with the file access mode `mode` and return the file descriptor.

```chaos
kaos> num fp = fs.open("files/readme.txt", "r")
```

The list of file access modes are
same as the `fopen` in C. (see [reference](https://en.cppreference.com/w/cpp/io/c/fopen))

### void fs.close(num file_descriptor)

Close a file given by the `file_descriptor`.

```chaos
kaos> fs.close(fp)
```

### str fs.read(num file_descriptor)

Read the contents of a file given by the `file_descriptor` into a string.

```chaos
kaos> num fp = fs.open("files/readme.txt", "r")
kaos> str text = fs.read(fp)
kaos> fs.close(fp)
kaos> print text
You read me!

```

### void fs.write(num file_descriptor, str text)

Write the contents to a file given by the `file_descriptor`.

```chaos
kaos> num fp = fs.open("files/writeme.txt", "w")
kaos> fs.write(fp, "You wrote me!\n")
kaos> fs.close(fp)
```

## Filesystem Operations

### void fs.move(str old_path, str new_path)

Move a file from `old_path` to `new_path`.

```chaos
kaos> fs.move("files/moveme.txt", "ignored/moveme.txt")
```

### void fs.copy(str src_filepath, str dst_filepath)

Copy the contents of a file on path `src_filepath` to a new file on `dst_filepath`.

```chaos
kaos> fs.copy("files/copyme.txt", "ignored/copyme.txt")
```

### bool fs.is_dir(str path)

Check if `path` is a directory.

```chaos
kaos> fs.is_dir("files/")
```

### bool fs.is_file(str path)

Check if `path` is a file.

```chaos
kaos> fs.is_file("files/readme.txt")
```
