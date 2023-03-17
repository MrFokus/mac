class User {
    constructor(name, age, email) {
        this.name = name;
        this.age = age;
        this.email = email;
    }
}

const users = [
    new User('John Doe', 1988, 'john.doe@mail.com'),
    new User('Jane Smith', 1990, 'jane.smith@mail.com'),
    new User('Bob Johnson', 1995, 'bob.johnson@mail.com')
];

function sortByAge(userList) {
    return userList.sort((a, b) => {
        return a.age - b.age;
    });
}

function sortByName(userList) {
    return userList.sort((a, b) => {
        if (a.name > b.name) {
            return -1;
        } else if (a.name > b.name) {
            return 1;
        } else {
            return 0;
        }
    });
}

console.log('Unsorted Users:', users);
console.log('Users Sorted by Age:', sortByAge(users));
console.log('Users Sorted by Name:', sortByName(users));
