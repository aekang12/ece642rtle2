#include <CUnit/Basic.h>
#include <sstream>
#include <string>
#include <iostream>
#include <cstdio>
#include "annkang_student_mock.h"

uint8_t memory[3] = {0,0,0};
int north = 1;
int& direction = north;
uint8_t tarray[24][24] = {0};

// Moved -> Moved bc path ahead is unvisited 
// check memory clear and tracker updated
void test_a1() {
  set_mock_state(Moved);
  set_mock_array(tarray);
  set_mock_x(11);
  set_mock_y(11); 
  set_mock_rrights(-1); 
  set_mock_rlefts(-1);
  set_mock_memory(memory);
  
  Moves next_move = studentTurtleStep(false, direction);
  State return_state = get_mock_state();
  uint8_t* output_memory = get_mock_memory();
  uint8_t visits = get_mock_visits(11, 12);
  uint8_t x = get_mock_x(); 
  uint8_t y = get_mock_y();  

  CU_ASSERT_EQUAL(output_memory[(uint8_t)Straight], 0);
  CU_ASSERT_EQUAL(output_memory[(uint8_t)Left], 0);
  CU_ASSERT_EQUAL(output_memory[(uint8_t)Right], 0);
  CU_ASSERT_EQUAL(return_state, Moved);
  CU_ASSERT_EQUAL(visits, 1);
  CU_ASSERT_EQUAL(x, 11); 
  CU_ASSERT_EQUAL(y, 12);
}

// Moved -> Turned_left bc path is visited or bumped
// check memory updated
void test_b1() {
  // test bumped
  set_mock_state(Moved);
  set_mock_array(tarray);
  set_mock_x(11);
  set_mock_y(11); 
  set_mock_rrights(-1); 
  set_mock_rlefts(-1);
  set_mock_memory(memory);
  Moves next_move = studentTurtleStep(true, direction);
  State return_state_bumped = get_mock_state();
  uint8_t* output_memory_bumped = get_mock_memory();

  CU_ASSERT_EQUAL(output_memory_bumped[(uint8_t)Straight], 100);
  CU_ASSERT_EQUAL(return_state_bumped, Turned_left);

  // test path visited
  uint8_t tarray_visited[24][24] = {0};
  tarray_visited[11][12] = 1;
  set_mock_state(Moved);
  set_mock_array(tarray_visited);
  set_mock_x(11);
  set_mock_y(11); 
  set_mock_rrights(-1); 
  set_mock_rlefts(-1);
  set_mock_memory(memory);

  next_move = studentTurtleStep(false, direction);
  State return_state_visited = get_mock_state();
  uint8_t* output_memory_visited = get_mock_memory();

  CU_ASSERT_EQUAL(output_memory_visited[(uint8_t)Straight], 1);
  CU_ASSERT_EQUAL(return_state_visited, Turned_left);
  
  // test path visited and bumped 
  tarray_visited[11][13] = 1;
  set_mock_state(Moved);
  set_mock_array(tarray_visited);
  set_mock_x(11);
  set_mock_y(12); 
  set_mock_rrights(-1); 
  set_mock_rlefts(-1);
  set_mock_memory(memory);

  next_move = studentTurtleStep(true, direction);
  return_state_visited = get_mock_state();
  output_memory_visited = get_mock_memory();

  CU_ASSERT_EQUAL(output_memory_visited[(uint8_t)Straight], 100);
  CU_ASSERT_EQUAL(return_state_visited, Turned_left);
}

// Turned_left -> turned_left bc remaining_lefts > 0
// check turned_left decremented
void test_c2() {
  set_mock_state(Turned_left);
  set_mock_array(tarray);
  set_mock_x(11);
  set_mock_y(11); 
  set_mock_rrights(-1); 
  set_mock_rlefts(2);
  set_mock_memory(memory);
  
  Moves next_move = studentTurtleStep(false, direction);
  State return_state = get_mock_state(); 
  int16_t remaining_lefts = get_mock_rlefts(); 

  CU_ASSERT_EQUAL(remaining_lefts, 1);
  CU_ASSERT_EQUAL(return_state, Turned_left);
}

// Turned_left -> Moved bc remaining_lefts = 0
// check memory cleared and tracker updated
void test_c3() {
  set_mock_state(Turned_left);
  set_mock_array(tarray);
  set_mock_x(11);
  set_mock_y(11); 
  set_mock_rrights(-1); 
  set_mock_rlefts(0);
  set_mock_memory(memory);
  
  Moves next_move = studentTurtleStep(false, direction);
  State return_state = get_mock_state();
  uint8_t* output_memory = get_mock_memory();
  uint8_t visits = get_mock_visits(11, 12);
  uint8_t x = get_mock_x(); 
  uint8_t y = get_mock_y();  

  CU_ASSERT_EQUAL(output_memory[(uint8_t)Straight], 0);
  CU_ASSERT_EQUAL(output_memory[(uint8_t)Left], 0);
  CU_ASSERT_EQUAL(output_memory[(uint8_t)Right], 0);
  CU_ASSERT_EQUAL(return_state, Moved);
  CU_ASSERT_EQUAL(visits, 1);
  CU_ASSERT_EQUAL(x, 11); 
  CU_ASSERT_EQUAL(y, 12);
}

// Turned_left -> Moved bc path is unvisited
// check clear memory and tracker updated
void test_a2() {
  set_mock_state(Turned_left);
  set_mock_array(tarray);
  set_mock_x(11);
  set_mock_y(11); 
  set_mock_rrights(-1); 
  set_mock_rlefts(-1);
  set_mock_memory(memory);
  
  Moves next_move = studentTurtleStep(false, direction);
  State return_state = get_mock_state();
  uint8_t* output_memory = get_mock_memory();
  uint8_t visits = get_mock_visits(11, 12);
  uint8_t x = get_mock_x(); 
  uint8_t y = get_mock_y();  

  CU_ASSERT_EQUAL(output_memory[(uint8_t)Straight], 0);
  CU_ASSERT_EQUAL(output_memory[(uint8_t)Left], 0);
  CU_ASSERT_EQUAL(output_memory[(uint8_t)Right], 0);
  CU_ASSERT_EQUAL(return_state, Moved);
  CU_ASSERT_EQUAL(visits, 1);
  CU_ASSERT_EQUAL(x, 11); 
  CU_ASSERT_EQUAL(y, 12);
}

// turned_left -> turned_right bc path is unvisited or bumped 
// check remaining_rights = 2 and memory updated 
void test_b2() {
  // test bumped
  set_mock_state(Turned_left);
  set_mock_array(tarray);
  set_mock_x(11);
  set_mock_y(11); 
  set_mock_rrights(-1); 
  set_mock_rlefts(-1);
  set_mock_memory(memory);
  Moves next_move = studentTurtleStep(true, direction);
  State return_state_bumped = get_mock_state();
  uint8_t* output_memory_bumped = get_mock_memory();
  int16_t rrights = get_mock_rrights(); 

  CU_ASSERT_EQUAL(output_memory_bumped[(uint8_t)Left], 100);
  CU_ASSERT_EQUAL(return_state_bumped, Turned_right);
  CU_ASSERT_EQUAL(rrights, 2);

  // test path visited
  uint8_t tarray_visited[24][24] = {0};
  tarray_visited[11][12] = 1;
  set_mock_state(Turned_left);
  set_mock_array(tarray_visited);
  set_mock_x(11);
  set_mock_y(11); 
  set_mock_rrights(-1); 
  set_mock_rlefts(-1);
  set_mock_memory(memory);

  next_move = studentTurtleStep(false, direction);
  State return_state_visited = get_mock_state();
  uint8_t* output_memory_visited = get_mock_memory();

  CU_ASSERT_EQUAL(output_memory_visited[(uint8_t)Left], 1);
  CU_ASSERT_EQUAL(return_state_visited, Turned_right);
  CU_ASSERT_EQUAL(rrights, 2);
  
  // test path visited and bumped
  tarray_visited[11][13] = 1;
  set_mock_state(Turned_left);
  set_mock_array(tarray_visited);
  set_mock_x(11);
  set_mock_y(12); 
  set_mock_rrights(-1); 
  set_mock_rlefts(-1);
  set_mock_memory(memory);

  next_move = studentTurtleStep(true, direction);
  return_state_visited = get_mock_state();
  output_memory_visited = get_mock_memory();

  CU_ASSERT_EQUAL(output_memory_visited[(uint8_t)Left], 100);
  CU_ASSERT_EQUAL(return_state_visited, Turned_right);
  CU_ASSERT_EQUAL(rrights, 2);
}

// Turned_right -> Turned_right bc remaining_rights = 0
void test_c1() {
  set_mock_state(Turned_right);
  set_mock_array(tarray);
  set_mock_x(11);
  set_mock_y(11); 
  set_mock_rrights(2); 
  set_mock_rlefts(-1);
  set_mock_memory(memory);
  
  Moves next_move = studentTurtleStep(false, direction);
  State return_state = get_mock_state(); 
  int16_t remaining_rights = get_mock_rrights(); 

  CU_ASSERT_EQUAL(remaining_rights, 1);
  CU_ASSERT_EQUAL(return_state, Turned_right);
}

// Turned_right -> moved bc path is unvisited
void test_a3() {
  set_mock_state(Turned_right);
  set_mock_array(tarray);
  set_mock_x(11);
  set_mock_y(11); 
  set_mock_rrights(-1); 
  set_mock_rlefts(-1);
  set_mock_memory(memory);
  
  Moves next_move = studentTurtleStep(false, direction);
  State return_state = get_mock_state();
  uint8_t* output_memory = get_mock_memory();
  uint8_t visits = get_mock_visits(11, 12);
  uint8_t x = get_mock_x(); 
  uint8_t y = get_mock_y();  

  CU_ASSERT_EQUAL(output_memory[(uint8_t)Straight], 0);
  CU_ASSERT_EQUAL(output_memory[(uint8_t)Left], 0);
  CU_ASSERT_EQUAL(output_memory[(uint8_t)Right], 0);
  CU_ASSERT_EQUAL(return_state, Moved);
  CU_ASSERT_EQUAL(visits, 1);
  CU_ASSERT_EQUAL(x, 11); 
  CU_ASSERT_EQUAL(y, 12);
}

// Turned_right -> Turned_left bc all paths are bumped 
// check remaining_lefts =3 
void test_d1() {
  uint8_t memory_bumped[3] = {100, 100, 100}; 
  uint8_t tarray_visited[24][24] = {0}; 
  tarray_visited[11][12] = 100; 
  set_mock_state(Turned_right);
  set_mock_array(tarray_visited);
  set_mock_x(11);
  set_mock_y(11); 
  set_mock_rrights(-1); 
  set_mock_rlefts(-1);
  set_mock_memory(memory_bumped);
  
  Moves next_move = studentTurtleStep(false, direction);
  State return_state = get_mock_state();
  uint8_t rlefts = get_mock_rlefts(); 

  CU_ASSERT_EQUAL(return_state, Turned_left);
  CU_ASSERT_EQUAL(rlefts, 3);
}

// Turned_right -> Turned_left bc left is least visited 
// check remaining_lefts = 2
void test_d2() {
  uint8_t memory_bumped[3] = {100, 1, 100}; 
  uint8_t tarray_visited[24][24] = {0}; 
  tarray_visited[11][12] = 100; 
  set_mock_state(Turned_right);
  set_mock_array(tarray_visited);
  set_mock_x(11);
  set_mock_y(11); 
  set_mock_rrights(-1); 
  set_mock_rlefts(-1);
  set_mock_memory(memory_bumped);
  
  Moves next_move = studentTurtleStep(false, direction);
  State return_state = get_mock_state();
  uint8_t rlefts = get_mock_rlefts(); 

  CU_ASSERT_EQUAL(return_state, Turned_left);
  CU_ASSERT_EQUAL(rlefts, 2);
}

// Turned_right -> Turned_left bc straight is least visited
// check remaining_lefts = 1
void test_d3() {
  uint8_t memory_bumped[3] = {100, 100, 1}; 
  uint8_t tarray_visited[24][24] = {0}; 
  tarray_visited[11][12] = 100; 
  set_mock_state(Turned_right);
  set_mock_array(tarray_visited);
  set_mock_x(11);
  set_mock_y(11); 
  set_mock_rrights(-1); 
  set_mock_rlefts(-1);
  set_mock_memory(memory_bumped);
  
  Moves next_move = studentTurtleStep(false, direction);
  State return_state = get_mock_state();
  uint8_t rlefts = get_mock_rlefts(); 

  CU_ASSERT_EQUAL(return_state, Turned_left);
  CU_ASSERT_EQUAL(rlefts, 1);
}

// Turned_right -> Moved bc right is least visited 
// check memory cleared and tracker updated 
void test_d4() {
  uint8_t memory_bumped[3] = {100, 100, 1}; 
  uint8_t tarray_visited[24][24] = {0}; 
  tarray_visited[11][12] = 1; 
  set_mock_state(Turned_right);
  set_mock_array(tarray_visited);
  set_mock_x(11);
  set_mock_y(11); 
  set_mock_rrights(-1); 
  set_mock_rlefts(-1);
  set_mock_memory(memory_bumped);
  
  Moves next_move = studentTurtleStep(false, direction);
  State return_state = get_mock_state();
  uint8_t* output_memory = get_mock_memory();
  uint8_t visits = get_mock_visits(11, 12);
  uint8_t x = get_mock_x(); 
  uint8_t y = get_mock_y();  

  CU_ASSERT_EQUAL(output_memory[(uint8_t)Straight], 0);
  CU_ASSERT_EQUAL(output_memory[(uint8_t)Left], 0);
  CU_ASSERT_EQUAL(output_memory[(uint8_t)Right], 0);
  CU_ASSERT_EQUAL(return_state, Moved);
  CU_ASSERT_EQUAL(visits, 2);
  CU_ASSERT_EQUAL(x, 11); 
  CU_ASSERT_EQUAL(y, 12);
}

void test_invalid() {
  std::ostringstream oss;
  std::streambuf* p_cout_streambuf = std::cout.rdbuf(); 
  std::cout.rdbuf(oss.rdbuf());

  set_mock_state(Sleeping);
  set_mock_array(tarray);
  set_mock_x(11);
  set_mock_y(11); 
  set_mock_rrights(-1); 
  set_mock_rlefts(-1);
  set_mock_memory(memory);
  
  Moves next_move = studentTurtleStep(false, direction);
  std::cout.rdbuf(p_cout_streambuf);

  CU_ASSERT_TRUE(oss.str() == "Invalid direction!");
  std::cout << oss.str();
}

int cleanup() {
  return 0; 
}

int init() {
  return 0;
}

int main() {

  CU_pSuite pSuite = NULL;

  /* initialize the CUnit test registry */
  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  /* add a suite to the registry */
  pSuite = CU_add_suite("Suite_1", init, cleanup);
  if (NULL == pSuite) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* add the tests to the suite */
  if ((NULL == CU_add_test(pSuite, "test of transition A1", test_a1)) ||
      (NULL == CU_add_test(pSuite, "test of transition B1", test_b1)) ||
      (NULL == CU_add_test(pSuite, "test of transition C1", test_c2)) ||
      (NULL == CU_add_test(pSuite, "test of transition C3", test_c3)) ||
      (NULL == CU_add_test(pSuite, "test of transition A2", test_a2)) ||
      (NULL == CU_add_test(pSuite, "test of transition B2", test_b2)) ||
      (NULL == CU_add_test(pSuite, "test of transition C1", test_c1)) ||
      (NULL == CU_add_test(pSuite, "test of transition A3", test_a3)) ||
      (NULL == CU_add_test(pSuite, "test of transition D1", test_d1)) ||
      (NULL == CU_add_test(pSuite, "test of transition D2", test_d2)) ||
      (NULL == CU_add_test(pSuite, "test of transition D3", test_d3)) ||
      (NULL == CU_add_test(pSuite, "test of transition D4", test_d4)) ||
      (NULL == CU_add_test(pSuite, "test of invalid direction", test_invalid)))
    {
      CU_cleanup_registry();
      return CU_get_error();
    }
  
  /* Run all tests using the CUnit Basic interface */
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_error();

  return 0;
}
