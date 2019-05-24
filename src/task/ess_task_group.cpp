#include "task/ess_task_group.h"

ess_error_t ess_task_group::start() {
  ess_autolock_t lock(*this);
  if(m_bIsStarted) return ESS_ERROR;

  m_bIsStarted = true;
  for(std::list<ess_task*>::iterator i = m_listTasks.begin(); i != m_listTasks.end(); ++i) {
    if( (*i)->start() != ESS_OK ) return ESS_ERROR;
  }
  return ESS_OK;
}
ess_error_t ess_task_group::start(uint32_t core)  {
  ess_autolock_t lock(*this);
  if(m_bIsStarted) return ESS_ERROR;
  
  m_bIsStarted = true;

  for(std::list<ess_task*>::iterator i = m_listTasks.begin(); i != m_listTasks.end(); ++i) {
    if( (*i)->start(core) != ESS_OK ) return ESS_ERROR;
  }
  return ESS_OK;
}
ess_error_t ess_task_group::destroy() {
  ess_autolock_t lock(*this);

  for(std::list<ess_task*>::iterator i = m_listTasks.begin(); i != m_listTasks.end(); ++i) {
    if( (*i)->destroy() != ESS_OK ) return ESS_ERROR;
  }
  return ESS_OK;
}
ess_error_t ess_task_group::suspend() {
  ess_autolock_t lock(*this);

  for(std::list<ess_task*>::iterator i = m_listTasks.begin(); i != m_listTasks.end(); ++i) {
    if( (*i)->suspend() != ESS_OK ) return ESS_ERROR;
  }
  return ESS_OK;
}
ess_error_t ess_task_group::resume() {
  ess_autolock_t lock(*this);

  for(std::list<ess_task*>::iterator i = m_listTasks.begin(); i != m_listTasks.end(); ++i) {
    if( (*i)->resume() != ESS_OK ) return ESS_ERROR;
  }
  return ESS_OK;
}

void ess_task_group::set_user_data(void* value) {
  ess_autolock_t lock(*this);

  for(std::list<ess_task*>::iterator i = m_listTasks.begin(); i != m_listTasks.end(); ++i) {
    (*i)->set_user_data(value);
  }
}
void ess_task_group::clear() {
  ess_autolock_t lock(*this);

  destroy();   m_listTasks.clear();
}
ess_error_t ess_task_group::add(ess_task* node) {
  if(m_bIsStarted) node->start();
  m_listTasks.push_back(node); return ESS_OK;
}
