#include "annkang_student_mock.h"
#include <CUnit/Basic.h>

struct Tracker{
    uint8_t array[23][23] = {};
    uint8_t x = 11; 
    uint8_t y = 11; 
} tracker_a;

struct Tracker{
    uint8_t array[23][23] = {};
    uint8_t x = 11; 
    uint8_t y = 11; 
} tracker_b;
tracker_b[11][12] = 1

void test_a1() {
  set_current_State(MOVE_FORWARD)
  set_tracker(tracker_a)
  set_memory({1,1,1})
  Moves next_move = studentTurtlestep(false, North);
  State return_state = test_state_result()
  uint8_t output_memory[3] = test_memory_result();

  CU_ASSERT_EQUAL(output_memory[(uint8_t)Straight], 0);
  CU_ASSERT_EQUAL(output_memory[(uint8_t)Left], 0);
  CU_ASSERT_EQUAL(output_memory[(uint8_t)Right], 0);
  CU_ASSERT_EQUAL(return_state, MOVE_FORWARD);
  CU_ASSERT_EQUAL(tracker_a.array[11][12], 1);
}

void test_b1() {
  set_current_State(MOVE_FORWARD)
  set_rlefts(-1)
  set_memory({0,0,1})
  Moves next_move = studentTurtlestep(true, North);
  State return_state_bumped = test_state_result()
  uint8_t output_memory_bumped[3] = test_memory_result();
  int16_t remaining_lefts_bumped = test_remaining_lefts_result(); 

  CU_ASSERT_EQUAL(output_memory_bumped[(uint8_t)Left], 100);
  CU_ASSERT_EQUAL(remaining_lefts_bumped, 0);
  CU_ASSERT_EQUAL(return_state_bumped, MOVE_FORWARD);

  set_current_State(MOVE_FORWARD);
  set_rlefts(-1);
  set_tracker(tracker_b);
  set_memory({0,0,1});
  Moves next_move = studentTurtlestep(false, North);
  return_state_visited = test_state_result()
  uint8_t output_memory_visited[3] = test_memory_result();
  int16_t remaining_lefts_visited = test_remaining_lefts_result(); 

  CU_ASSERT_EQUAL(output_memory_visited[(uint8_t)Left], 0);
  CU_ASSERT_EQUAL(remaining_lefts_visited, 0);
  CU_ASSERT_EQUAL(return_state_visited, MOVE_FORWARD);
}

void test_c2() {
  set_current_State(TURNED_LEFT)
  set_rlefts(2)
  set_memory(memory)
  Moves next_move = studentTurtlestep(false, North);
  State return_state = test_state_result() 
  int16_t remaining_lefts = test_remaining_lefts_result(); 

  CU_ASSERT_EQUAL(output_memory[(uint8_t)Left], 0);
  CU_ASSERT_EQUAL(remaining_lefts, 1);
  CU_ASSERT_EQUAL(return_state, TURNED_LEFT);
}

void test_c3() {
  set_current_State(TURNED_LEFT)
  set_rlefts(0)
  set_tracer(tracker_c3)
  set_memory(memory)
  Moves next_move = studentTurtlestep(false, North);
  State return_state = test_state_result()
  int16_t remaining_lefts = test_remaining_lefts_result(); 

  CU_ASSERT_EQUAL(output_memory[(uint8_t)Straight], 0);
  CU_ASSERT_EQUAL(output_memory[(uint8_t)Left], 0);
  CU_ASSERT_EQUAL(output_memory[(uint8_t)Right], 0);
  // tracker
  CU_ASSERT_EQUAL(return_state, MOVE_FORWARD);
}

void test_a2() {
  set_current_State(TURNED_LEFT);
  set_tracker(tracker);
  set_memory(memory);
  Moves next_move = studentTurtlestep(false, North);
  State return_state = test_state_result();
  uint8_t output_memory[3] = test_memory_result();
  // tracker??

  CU_ASSERT_EQUAL(output_memory[(uint8_t)Straight], 0);
  CU_ASSERT_EQUAL(output_memory[(uint8_t)Left], 0);
  CU_ASSERT_EQUAL(output_memory[(uint8_t)Right], 0);
  CU_ASSERT_EQUAL(return_state, MOVE_FORWARD);
}

void test_b2() {
  set_current_State(TURNED_LEFT);
  set_rrights(2);
  set_rlefts(-1);
  set_memory(memory);
  Moves next_move = studentTurtlestep(true, North);
  return_state_bumped = test_state_result();
  uint8_t output_memory_bumped[3] = test_memory_result();
  int16_t remaining_rights_bumped = test_remaining_rights_result(); 

  CU_ASSERT_EQUAL(output_memory_bumped[(uint8_t)Right], 100);
  CU_ASSERT_EQUAL(remaining_rights_bumped, 2);
  CU_ASSERT_EQUAL(return_state_bumped, TURNED_RIGHT);

  set_current_State(TURNED_LEFT);
  set_rlefts(2);
  set_rlefts(-1);
  set_tracker(tracker_b2_visited);
  set_memory(memory);
  Moves next_move = studentTurtlestep(false, North);
  return_state_visited = test_state_result();
  uint8_t output_memory_visited[3] = test_memory_result();
  int16_t remaining_rights_visited = test_remaining_rights_result(); 

  CU_ASSERT_EQUAL(output_memory_visited[(uint8_t)Right], 0);
  CU_ASSERT_EQUAL(remaining_rights_visited, 2);
  CU_ASSERT_EQUAL(return_state_visited, TURNED_RIGHT);
}

void test_c1() {
  set_current_State(TURNED_RIGHT);
  set_rrights(2);
  set_memory(memory);
  Moves next_move = studentTurtlestep(false, North);
  return_state = test_state_result();
  int16_t remaining_rights = test_remaining_rights_result(); 

  CU_ASSERT_EQUAL(output_memory[(uint8_t)Right], 0);
  CU_ASSERT_EQUAL(remaining_rights, 1);
  CU_ASSERT_EQUAL(return_state, TURNED_RIGHT);
}

void test_a3() {
  set_current_State(TURNED_RIGHT);
  set_tracker(tracker);
  set_memory(memory);
  Moves next_move = studentTurtlestep(false, North);
  State return_state = test_state_result();
  uint8_t output_memory[3] = test_memory_result();
  // tracker??

  CU_ASSERT_EQUAL(output_memory[(uint8_t)Straight], 0);
  CU_ASSERT_EQUAL(output_memory[(uint8_t)Left], 0);
  CU_ASSERT_EQUAL(output_memory[(uint8_t)Right], 0);
  CU_ASSERT_EQUAL(return_state, MOVE_FORWARD);
}

void test_d1() {
  set_current_State(TURNED_RIGHT);
  set_memory(memory);
  set_rrights(-1);
  Moves next_move = studentTurtlestep(true, North);
  State return_state = test_state_result();
  uint8_t output_memory[3] = test_memory_result();
  // tracker??

  CU_ASSERT_EQUAL(output_memory[(uint8_t)Right], 0);
  CU_ASSERT_EQUAL(remaining_lefts, 3);
  CU_ASSERT_EQUAL(return_state, TURNED_LEFT);
}

void test_d2() {
  set_current_State(TURNED_RIGHT);
  set_memory(memory);
  set_rrights(-1);
  Moves next_move = studentTurtlestep(true, North);
  State return_state = test_state_result();
  uint8_t output_memory[3] = test_memory_result();
  // tracker??

  CU_ASSERT_EQUAL(output_memory[(uint8_t)Right], 100);
  CU_ASSERT_EQUAL(remaining_lefts, 2);
  CU_ASSERT_EQUAL(return_state, TURNED_LEFT);
}

void test_d1() {
  set_current_State(TURNED_RIGHT);
  set_memory(memory);
  set_rrights(-1);
  Moves next_move = studentTurtlestep(true, North);
  State return_state = 
  uint8_t output_memory[3] = test_memory_result();
  // tracker??

  CU_ASSERT_EQUAL(output_memory[(uint8_t)Right], 100);
  CU_ASSERT_EQUAL(remaining_lefts, 1);
  CU_ASSERT_EQUAL(return_state, TURNED_LEFT);
}

void test_d4() {
  set_current_State(TURNED_RIGHT);
  set_memory(memory);
  set_rrights(-1);
  Moves next_move = studentTurtlestep(true, North);
  State return_state = test_state_result;
  uint8_t output_memory[3] = test_memory_result();
  // tracker??

  CU_ASSERT_EQUAL(output_memory[(uint8_t)Straight], 0);
  CU_ASSERT_EQUAL(output_memory[(uint8_t)Left], 0);
  CU_ASSERT_EQUAL(output_memory[(uint8_t)Right], 0);
  CU_ASSERT_EQUAL(return_state, MOVE_FORWARD);
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