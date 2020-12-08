Filesystem interface library of the Chaos language. You can install this spell with:
```
occultist install fs
```

and import it with:
```
import fs
```

## Filesystem operations

### void fs.copy(str src_filepath, str dst_filepath)

Copy the contents of a file to a new file.

```
kaos> fs.copy("README.txt", "README.md")
```
