// Copyright 2024 GOTHAM Inc. All Rights Reserved.
// Author: easytojoin@163.com (jok)

package main

import (
	"runtime"
	"sync/atomic"
	"time"
)

type SpinLock uint32

func (s_l *SpinLock) Lock() {
	for !atomic.CompareAndSwapUint32((*uint32)(s_l), 0, 1) {
		runtime.Gosched()
	}
}

func (s_l *SpinLock) UnLock() {
	atomic.StoreUint32((*uint32)(s_l), 0)
}

func NewSpinLock() *SpinLock {
	return new(SpinLock)
}

func main() {
	lock := NewSpinLock()
	lock.Lock()
	time.Sleep(1 * time.Second)
	lock.UnLock()
}
