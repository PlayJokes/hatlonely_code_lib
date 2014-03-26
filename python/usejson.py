import json


obj = '''{
    "name": "hatlonely",
    "email": "hatlonely@gmail.com",
    "age": 9,
    "array": ["a", "b"]
}'''

print(json.loads(obj))

obj = json.loads(obj)

print(obj['name'])
print(obj['email'])
print(obj['age'])
print(obj['array'])

hehe = {
    "name": "hatlonely",
    "email": "hatlonely@gmail.com",
    "age": 9,
    "array": ["a", "b"]
}

print(hehe)