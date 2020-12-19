Filesystem interface library of the Chaos language. You can install this spell with:

```bash
occultist install fs
```

and import it with:

```chaos
import fs
```

## Filesystem Operations

### num fs.open(str filepath)

Open a file on path `filepath` and return the file descriptor.

```chaos
kaos> num fp = fs.open("files/readme.txt")
```

### void fs.close(num file_descriptor)

Close a file given by the `file_descriptor`.

```chaos
kaos> fs.close(fp)
```

### str fs.read(num file_descriptor)

Read the contents of a file given by the `file_descriptor` into a string.

```chaos
kaos> str text = fs.read(fp)
kaos> print text
You read me!

```

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
