#include "annkang_student_turtle.cpp"
#include <CUnit/Basic.h>

void test_a1() {
  uint8_t memory[3] = {0,0,1};
  int north = 1;
  int& direction = north;
  uint8_t tarray[24][24] = {0};

  set_current_state(Moved);
  set_tracker(tarray, 11, 11);
  set_memory(memory);
  Moves next_move = studentTurtleStep(false, direction);
  State return_state = test_state_result();
  uint8_t* output_memory = test_memory_result();
  uint8_t visits = test_tracker(11, 12); 

  CU_ASSERT_EQUAL(output_memory[(uint8_t)Straight], 0);
  CU_ASSERT_EQUAL(output_memory[(uint8_t)Left], 0);
  CU_ASSERT_EQUAL(output_memory[(uint8_t)Right], 0);
  CU_ASSERT_EQUAL(return_state, Moved);
  CU_ASSERT_EQUAL(visits, 1);
}

void test_b1() {
  uint8_t memory[3] = {0,0,1};
  int north = 1;
  int& direction = north;

  set_current_state(Moved);
  set_rlefts(-1);
  set_memory(memory);
  Moves next_move = studentTurtleStep(true, direction);
  State return_state_bumped = test_state_result();
  uint8_t* output_memory_bumped = test_memory_result();
  int16_t remaining_lefts_bumped = test_remaining_lefts_result(); 

  CU_ASSERT_EQUAL(output_memory_bumped[(uint8_t)Left], 100);
  CU_ASSERT_EQUAL(remaining_lefts_bumped, 0);
  CU_ASSERT_EQUAL(return_state_bumped, Turned_left);

  set_current_state(Moved);
  set_rlefts(-1);
  set_memory(memory);
  next_move = studentTurtleStep(false, direction);
  State return_state_visited = test_state_result();
  uint8_t* output_memory_visited = test_memory_result();
  int16_t remaining_lefts_visited = test_remaining_lefts_result(); 

  CU_ASSERT_EQUAL(output_memory_visited[(uint8_t)Left], 0);
  CU_ASSERT_EQUAL(remaining_lefts_visited, 0);
  CU_ASSERT_EQUAL(return_state_visited, Turned_left);
}

//void test_c2() {
//  set_current_state(Turned_left)
//  set_remaining_lefts(2)
//  set_memory(memory)
//  Moves next_move = studentTurtleStep(false, North);
//  State return_state = test_state_result() 
//  int16_t remaining_lefts = test_remaining_lefts_result(); 
//
//  CU_ASSERT_EQUAL(output_memory[(uint8_t)Left], 0);
//  CU_ASSERT_EQUAL(remaining_lefts, 1);
//  CU_ASSERT_EQUAL(return_state, Turned_left);
//}
//
//void test_c3() {
//  set_current_state(Turned_left)
//  set_remaining_lefts(0)
//  set_tracer(tracker_c3)
//  set_memory(memory)
//  Moves next_move = studentTurtleStep(false, North);
//  State return_state = test_state_result()
//  int16_t remaining_lefts = test_remaining_lefts_result(); 
//
//  CU_ASSERT_EQUAL(output_memory[(uint8_t)Straight], 0);
//  CU_ASSERT_EQUAL(output_memory[(uint8_t)Left], 0);
//  CU_ASSERT_EQUAL(output_memory[(uint8_t)Right], 0);
//  // tracker
//  CU_ASSERT_EQUAL(return_state, Moved);
//}
//
//void test_a2() {
//  set_current_state(Turned_left);
//  set_tracker(tracker);
//  set_memory(memory);
//  Moves next_move = studentTurtleStep(false, North);
//  State return_state = test_state_result();
//  uint8_t output_memory[3] = test_memory_result();
//  // tracker??
//
//  CU_ASSERT_EQUAL(output_memory[(uint8_t)Straight], 0);
//  CU_ASSERT_EQUAL(output_memory[(uint8_t)Left], 0);
//  CU_ASSERT_EQUAL(output_memory[(uint8_t)Right], 0);
//  CU_ASSERT_EQUAL(return_state, Moved);
//}
//
//void test_b2() {
//  set_current_state(Turned_left);
//  set_remaining_rights(2);
//  set_remaining_lefts(-1);
//  set_memory(memory);
//  Moves next_move = studentTurtleStep(true, North);
//  return_state_bumped = test_state_result();
//  uint8_t output_memory_bumped[3] = test_memory_result();
//  int16_t remaining_rights_bumped = test_remaining_rights_result(); 
//
//  CU_ASSERT_EQUAL(output_memory_bumped[(uint8_t)Right], 100);
//  CU_ASSERT_EQUAL(remaining_rights_bumped, 2);
//  CU_ASSERT_EQUAL(return_state_bumped, Turned_right);
//
//  set_current_state(Turned_left);
//  set_remaining_lefts(2);
//  set_remaining_lefts(-1);
//  set_tracker(tracker_b2_visited);
//  set_memory(memory);
//  Moves next_move = studentTurtleStep(false, North);
//  return_state_visited = test_state_result();
//  uint8_t output_memory_visited[3] = test_memory_result();
//  int16_t remaining_rights_visited = test_remaining_rights_result(); 
//
//  CU_ASSERT_EQUAL(output_memory_visited[(uint8_t)Right], 0);
//  CU_ASSERT_EQUAL(remaining_rights_visited, 2);
//  CU_ASSERT_EQUAL(return_state_visited, Turned_right);
//}
//
//void test_c1() {
//  set_current_state(Turned_right);
//  set_remaining_rights(2);
//  set_memory(memory);
//  Moves next_move = studentTurtleStep(false, North);
//  return_state = test_state_result();
//  int16_t remaining_rights = test_remaining_rights_result(); 
//
//  CU_ASSERT_EQUAL(output_memory[(uint8_t)Right], 0);
//  CU_ASSERT_EQUAL(remaining_rights, 1);
//  CU_ASSERT_EQUAL(return_state, Turned_right);
//}
//
//void test_a3() {
//  set_current_state(Turned_right);
//  set_tracker(tracker);
//  set_memory(memory);
//  Moves next_move = studentTurtleStep(false, North);
//  State return_state = test_state_result();
//  uint8_t output_memory[3] = test_memory_result();
//  // tracker??
//
//  CU_ASSERT_EQUAL(output_memory[(uint8_t)Straight], 0);
//  CU_ASSERT_EQUAL(output_memory[(uint8_t)Left], 0);
//  CU_ASSERT_EQUAL(output_memory[(uint8_t)Right], 0);
//  CU_ASSERT_EQUAL(return_state, Moved);
//}
//
//void test_d1() {
//  set_current_state(Turned_right);
//  set_memory(memory);
//  set_remaining_rights(-1);
//  Moves next_move = studentTurtleStep(true, North);
//  State return_state = test_state_result();
//  uint8_t output_memory[3] = test_memory_result();
//  // tracker??
//
//  CU_ASSERT_EQUAL(output_memory[(uint8_t)Right], 0);
//  CU_ASSERT_EQUAL(remaining_lefts, 3);
//  CU_ASSERT_EQUAL(return_state, Turned_left);
//}
//
//void test_d2() {
//  set_current_state(Turned_right);
//  set_memory(memory);
//  set_remaining_rights(-1);
//  Moves next_move = studentTurtleStep(true, North);
//  State return_state = test_state_result();
//  uint8_t output_memory[3] = test_memory_result();
//  // tracker??
//
//  CU_ASSERT_EQUAL(output_memory[(uint8_t)Right], 100);
//  CU_ASSERT_EQUAL(remaining_lefts, 2);
//  CU_ASSERT_EQUAL(return_state, Turned_left);
//}
//
//void test_d3() {
//  set_current_state(Turned_right);
//  set_memory(memory);
//  set_remaining_rights(-1);
//  Moves next_move = studentTurtleStep(true, North);
//  State return_state = 
//  remaining_lefts = test_rlefts_result(); 
//  uint8_t output_memory[3] = test_memory_result();
//  // tracker??
//
//  CU_ASSERT_EQUAL(output_memory[(uint8_t)Right], 100);
//  CU_ASSERT_EQUAL(remaining_lefts, 1);
//  CU_ASSERT_EQUAL(return_state, Turned_left);
//}
//
//void test_d4() {
//  set_current_state(Turned_right);
//  set_memory(memory);
//  set_remaining_rights(-1);
//  Moves next_move = studentTurtleStep(true, North);
//  State return_state = test_state_result();
//  uint8_t* output_memory = test_memory_result();
//  // tracker??
//
//  CU_ASSERT_EQUAL(output_memory[(uint8_t)Straight], 0);
//  CU_ASSERT_EQUAL(output_memory[(uint8_t)Left], 0);
//  CU_ASSERT_EQUAL(output_memory[(uint8_t)Right], 0);
//  CU_ASSERT_EQUAL(return_state, Moved);
//}

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
      (NULL == CU_add_test(pSuite, "test of transition B1", test_b1)))
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
