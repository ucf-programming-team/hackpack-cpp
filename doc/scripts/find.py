import os
import re

pat = r"\\kactlimport(?:\[.*?\])?\{(.*?)\}"
r = re.compile(pat)

def find_inside(file):
    have = set()
    for match in r.finditer(file.read()):
        have.add(match.group(1))
    return have

for z in range(2):
    for folder in os.scandir("content/"):
        if folder.is_dir():
            in_print = set()
            found = set()
            both = set()
            for filename in os.scandir(folder.path):
                if filename.name == "chapter.tex":
                    with open(filename.path, "r") as f:
                        in_print = find_inside(f)
                if ".pdf" not in filename.name and ".tex" not in filename.name:
                    found.add(filename.name)
                
                both = found & in_print
                
            if found == in_print:
                continue


            if z:
                print(folder.name)
                if len(found - both):
                    print("Found but not printed:")
                    print(found - both)
                if len(in_print - both):
                    print("Printed but not found:")
                    print(in_print - both)
                print()
            elif found != both:
                print(f"adding to {folder.name}")
                print(found - both)
                print()

                with open(folder.path + "/chapter.tex", "a") as f:
                    f.write("\n")
                    f.write("% extra stuff found\n")
                    f.writelines("\\kactlimport{!}\n".replace("!", s) for s in found - both)

# with open("content/strings/chapter.tex", "r") as f:
#     find_inside(f)

