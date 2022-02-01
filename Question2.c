#include <stdio.h>
#include <stdlib.h>
#include "Questions.h"

student **create_class_list(char *filename, int *sizePtr){

    student **class_list;
    int num_of_students;
    int i;

    FILE *student_List = fopen(filename, "r");
    fscanf(student_List,"%d",&num_of_students); //scans number of students
    *sizePtr = num_of_students;
    class_list = (student**)malloc(num_of_students*sizeof(student*)); //assigns memories for pointers
    for(i=0; i<num_of_students; i++){
        class_list[i] = (student*)calloc(1,sizeof(student));
        fscanf(student_List, "%d %s %s", &class_list[i]->student_id, class_list[i]->first_name, class_list[i]->last_name); //scans studentID, first name and last name
    }
    fclose(student_List);
    return class_list;
}

int find(int idNo, student **list, int size){
    for(int j =0; j<size; j++){ //loops until student_id is found
        if(list[j]->student_id == idNo){
            return j; //exits when student_id is found
        }
    }
    return -1; //if student_id is not found, returns -1
}

void input_grades(char *filename, student **list, int size){
    FILE *gradeList = fopen(filename, "r");
    int current_Student;
    int position;
    for(int j=0; j<size; j++){ //reads through the file which contains grades
        fscanf(gradeList, "%d", &current_Student);
        position = find(current_Student, list, size);
        if(position!=-1){
            fscanf(gradeList, "%d %d", &list[position]->project1_grade, &list[position]->project2_grade);  //inputs project1_grade and project2_grade
        }
    }
    fclose(gradeList); //closes file
}

void compute_final_course_grades(student **list, int size){
    for(int j=0; j<size; j++){ //loops through each student grades
        list[j]->final_grade = (list[j]->project1_grade + list[j]->project2_grade)/2.0; //finds average
    }
}

void output_final_course_grades(char *filename, student **list, int size){
    FILE *finalGrades = fopen(filename,"w"); //to write, a file is opened
    fprintf(finalGrades,"%d\n",size); //prints number of students
    for(int j=0; j<size; j++){ //loops through print id and grade
        fprintf(finalGrades,"%d %f\n", list[j]->student_id, list[j]->final_grade);
    }
    fclose(finalGrades); //closes file
}


void withdraw(int idNo, student **list, int* sizePtr){
    int exists = 0, count = 0, j;
    for(j=0; j<*sizePtr; j++){
        if(list[j]->student_id == idNo){
            exists = 1; //if student asked belong to the student in list, set exits to 1
            break; //exits for loop
        }
    }
    if(exists){
        free(list[j]);
        for(int i=j+1; i<*sizePtr; i++){
            list[i-1] = list[i];
        }
        *sizePtr-=1;
        printf("The student with the student ID of %d has been withdrawn from the list.\n", idNo);
    }
    else //if studentID is not in list of students
    {
        printf("That student is not in this list.\n");
    }
}

void destroy_list(student **list, int *sizePtr){
    for(int j=0; j<*sizePtr; j++){
        free(list[j]);}
    free(list);
    *sizePtr = 0;
}
