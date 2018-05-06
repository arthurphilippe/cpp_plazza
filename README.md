# Plazza scrapper project

[![CircleCI](https://circleci.com/gh/arthurphilippe/cpp_plazza/tree/master.svg?style=svg&circle-token=fbfbbddcef5b88fd321cbaefe8fa8b4fb567c0b6)](https://circleci.com/gh/arthurphilippe/cpp_plazza/tree/master)

## Install
### CLI
Run
```sh
make
```

### Graphical
Run
```sh
make ui
```

## Usage
Launch either `./plazza` or `./PlazzaGui` followed by the number of thread a process is allowed to have.

For instance :
```
./plazza 5
```
Will launch plazza with a maximum of 5 threads per scrapper.
