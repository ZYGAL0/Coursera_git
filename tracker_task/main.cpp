#include <iostream>
#include <map>
#include <tuple>
#include <vector>

using namespace std;

// Перечислимый тип для статуса задачи
enum class TaskStatus {
    NEW,          // новая
    IN_PROGRESS,  // в разработке
    TESTING,      // на тестировании
    DONE          // завершена
};

// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = map<TaskStatus, int>;

void RemoveZeros (TasksInfo& change) {
    vector<TaskStatus> stat_to_remove;
    for (const auto & item : change) {
        if (item.second == 0) {
            stat_to_remove.push_back(item.first);
        }
    }
    for (const auto rem : stat_to_remove) {
        change.erase(rem);
    }
}

TaskStatus Next(TaskStatus task_status) {
    return static_cast<TaskStatus>(static_cast<int>(task_status) + 1);
}

class TeamTasks {
private:
    map<string, TasksInfo> Programmers;
public:
    // Получить статистику по статусам задач конкретного разработчика
    [[nodiscard]] const TasksInfo &GetPersonTasksInfo(const string &person) const {
        return Programmers.at(person);
    }

    // Добавить новую задачу (в статусе NEW) для конкретного разработчитка
    void AddNewTask(const string &person) {
        Programmers[person][TaskStatus::NEW]++;
    }

    // Обновить статусы по данному количеству задач конкретного разработчика,
    // подробности см. ниже
    tuple<TasksInfo, TasksInfo> PerformPersonTasks(const string &person, int task_count) {
        vector<TaskStatus> special = {TaskStatus::NEW, TaskStatus::IN_PROGRESS, TaskStatus::TESTING, TaskStatus::DONE};
        TasksInfo Old = Programmers[person];
        TasksInfo New;
        task_count = min(task_count, Old[TaskStatus::NEW] +
                                     Old[TaskStatus::IN_PROGRESS] +
                                     Old[TaskStatus::TESTING]);
        for (int i = 0; i < task_count; i++) {
            for (const auto &item : special) {
                if (Programmers[person][item] > New[Next(item)]) {
                    New[Next(item)]++;
                    Old[item]--;
                    break;
                }
            }
        }
        for (const auto & item : special) {
            Programmers[person][item] = New[item] + Old[item];
        }

        Old.erase(TaskStatus::DONE);

        RemoveZeros(New);
        RemoveZeros(Old);
        RemoveZeros(Programmers[person]);

        auto res = make_tuple(New, Old);
        return res;
    }
};

// Принимаем словарь по значению, чтобы иметь возможность
// обращаться к отсутствующим ключам с помощью [] и получать 0,
// не меняя при этом исходный словарь
void PrintTasksInfo(TasksInfo tasks_info) {
    cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
         ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
         ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
         ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}

int main() {
    TeamTasks tasks;
//    AddNewTasks Alice 5
//    PerformPersonTasks Alice 5
//    PerformPersonTasks Alice 5
//    PerformPersonTasks Alice 1
//    AddNewTasks Alice 5
//    PerformPersonTasks Alice 2
//    GetPersonTasksInfo Alice
//    PerformPersonTasks Alice 4
//    GetPersonTasksInfo Alice

    for (int i = 0; i < 5; ++i) {
        tasks.AddNewTask("Ivan");
    }
    cout << "Ivan's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));

    TasksInfo updated_tasks, untouched_tasks;

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan", 5);
    cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);

    cout << "Ivan's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan", 5);
    cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan", 1);
    cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);

    for (int i = 0; i < 5; ++i) {cout << "Ivan's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));
        tasks.AddNewTask("Ivan");
    }

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan", 2);
    cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);

    cout << "Ivan's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan", 4);
    cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);

    cout << "Ivan's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));

    return 0;
}