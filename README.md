Filesystem interface library of the Chaos language. You can install this spell with:

```bash
occultist install fs
```

and import it with:

```chaos
import fs
```

## Filesystem operations

### str fs.read(str filepath)

Read the contents of a file on path `src_filepath` into a string.

```chaos
kaos> str text = fs.read('files/readme.txt')
kaos> print text
You read me!

```

### void fs.copy(str src_filepath, str dst_filepath)

Copy the contents of a file on path `src_filepath` to a new file on `dst_filepath`.

```chaos
kaos> fs.copy("files/copyme.txt", "ignored/copyme.txt")
```

### bool fs.is_dir(str path)

Check if `path` is a directory.

```chaos
kaos> fs.is_dir('/home/user/')
```

### bool fs.is_file(str path)

Check if `path` is a file.

```chaos
kaos> fs.is_file('home/user/.bashrc')
```

### void fs.rename(str oldpath, str newpath)

Rename file `oldpath` to `newpath`.

```chaos
kaos> fs.rename('hello.txt', 'goodbye.txt')
```
