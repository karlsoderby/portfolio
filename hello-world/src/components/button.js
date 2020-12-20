import React from "react"
import containerStyles from "./container.module.css"

export default function Largebutton({ children }) {
  return (
    <a className={containerStyles.largebutton}>{children}</a>
    
  )
}

