#!/usr/bin/env python2

import json
import re
import os

# Creates VSCode JSON snippets out of hackpack code
# running this file directly combines all of the snippets into one
# build() is called from the preprocessor to build the individual file snippets

prefix = 'hack_'
langs = {
    'C++': 'cpp',
    'Java': 'java',
    'Python': 'python' 
}
pattern = re.compile(r'^(\t*) {2}')

# convert a line that starts with tabs into one that starts with spaces
def spaces_to_tabs(str):
    while pattern.match(str):
        str = pattern.sub(r'\1\t', str)
    return str

# create a snippet for a single file, and put it in snippets/lang/name.json
# called from the preprocessor
def build(filename, commands, nsource, lang):

    # do not make the snippet if it's not code
    if lang not in langs:
        return

    name = filename.split('.')[0]

    # build json object
    obj = {}
    obj['prefix'] = [prefix + name]
    obj['body'] = [spaces_to_tabs(line) for line in nsource.split('\n')]

    if 'Description' in commands:
        obj['description'] = commands['Description']

    path = 'snippets/' + langs[lang] + '/'

    if not os.path.exists(path):
        os.makedirs(path)
    
    # dump json object into file
    f = open(path + name + '.json', 'w')
    json.dump({filename: obj}, f, indent=4, sort_keys=True)
    f.close()
    return {filename: obj}

# reads all of the snippets in a lang's snippet folder, and combines them into one
# works with C++, should work with Java and Python as well (in theory) 
def combine():
    for key in langs:
        lang = langs[key]
        lang_obj = {}
        lang_path = 'snippets/' + lang + '/'

        # don't make empty files
        if not os.path.isdir(lang_path):
            continue
            
        # dump each json object into the lang's master object
        for filename in os.listdir(lang_path):
            f = open(lang_path + filename, 'r')
            lang_obj.update(json.load(f))

        # dump nonempty json object into file
        if len(lang_obj) > 0:
            path = 'snippets/' + lang + '.json'
            f = open(path, 'w')
            json.dump(lang_obj, f, indent=4, sort_keys=True)
            f.close()

def main():
    combine()
        
if __name__ == "__main__":
    main()
